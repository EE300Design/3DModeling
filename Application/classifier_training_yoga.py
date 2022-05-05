# import matplotlib.pyplot as plt
import numpy as np
import os
import PIL
import tensorflow as tf

from tensorflow import keras
from tensorflow.keras import layers
from tensorflow.keras.models import Sequential

import pathlib

dir = "data"

def parse_image(filename):

  parts = tf.strings.split(filename, os.sep)
  label = parts[-2]

  image = tf.io.read_file(filename)
  image = tf.io.decode_jpeg(image)
  image = tf.image.convert_image_dtype(image, tf.float32)
  return image, label

data_dir = pathlib.Path(dir)
print(data_dir)
images = data_dir.glob('*/*.png')
print(len(list(images)))


cubes = list(data_dir.glob('cubes/*.png'))
cylinders = list(data_dir.glob('cylinders/*.png'))

PIL.Image.open(str(cubes[int(100*np.random.random())]))



batch_size = 32
img_height = 50
img_width = 200
seed = 12

train_ds = tf.keras.utils.image_dataset_from_directory(
    data_dir,
    validation_split = .2,
    subset = "training",
    shuffle=True,
    image_size=(img_height, img_width),
    batch_size = batch_size,
    seed = seed,
    color_mode = 'grayscale'
)
val_ds = tf.keras.utils.image_dataset_from_directory(
    data_dir,
    validation_split = .2,
    subset = "validation",
    shuffle=True,
    image_size=(img_height, img_width),
    batch_size = batch_size,
    seed = seed,
    color_mode = 'grayscale'
)


def parse_image(filename):
    parts = tf.strings.split(filename, os.sep)
    label = parts[-2]

    image = tf.io.read_file(filename)


batch_size = 32
img_height = 50
img_width = 200

# normalization_layer = layers.Rescaling(1./255)
class_names = train_ds.class_names

print(class_names)
AUTOTUNE = tf.data.AUTOTUNE
train_ds = train_ds.cache().shuffle(1000).prefetch(buffer_size=AUTOTUNE)
val_ds = val_ds.cache().prefetch(buffer_size=AUTOTUNE)

model = tf.keras.Sequential([
    tf.keras.layers.Flatten(input_shape=(50, 200)),
    tf.keras.layers.Dense(128, activation='relu'),
    tf.keras.layers.Dense(128, activation='relu'),
    tf.keras.layers.Dense(128, activation='relu'),
    tf.keras.layers.Dense(2)
])

model.compile(optimizer='adam',
              loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
              metrics=['accuracy'])


model.summary()


epochs=50
history = model.fit(
  train_ds,
  validation_data=val_ds,
  epochs=epochs
)

model.save('Cube_Cyl_class_model_yoga')