import numpy as np
import os
import tensorflow as tf

from tensorflow import keras
from tensorflow.keras import layers
from tensorflow.keras.models import Sequential

from PIL import Image

model = tf.keras.models.load_model('Cube_Cyl_class_model_yoga')

test = Image.open('data/cubes/cube0.png')
temp = np.array(test)
temp = (np.expand_dims(temp,0))
# y_tensor = tf.convert_to_tensor(temp, dtype=tf.int64)

print(temp.shape)
result = (model.predict(temp))
print(result.shape)
if result[0,0]>result[0,1]:
    print('Cube')
else:
    print('Cylinder')