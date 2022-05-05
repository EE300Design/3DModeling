import numpy as np
import os

import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
from tensorflow.keras.models import Sequential

from PIL import Image

model = tf.keras.models.load_model('Cube_Cyl_class_model_yoga')

temp = np.genfromtxt('test.csv',delimiter=',',dtype=float)
m  = temp.max()
n = temp.min()
PIL_image = Image.fromarray(np.uint8((temp-n)* 255/(m-n)) , 'L')
resized_Image = PIL_image.resize((200,50),Image.BILINEAR)

resized_Image.save("temp.png","PNG")

temp = np.array(resized_Image)
temp = (np.expand_dims(temp,0))

result = (model.predict(temp))

if result[0,0]>result[0,1]:
    print('Cube')
else:
    print('Cylinder')