from stl import mesh
from mpl_toolkits import mplot3d
from matplotlib import pyplot
import numpy as np
import cylinder_generation as gen
from PIL import Image


m,n = 50,200

file_length = 200
noise = 1e-1

for i in range(file_length):

	cube = gen.create_cube(m,n,rot_ax = (3e-1*np.random.rand(1,2)),noise=noise)

	max_r = cube.max()
	min_r = cube.min()
	image_data = (cube-min_r)/(max_r-min_r)

	# PIL_image = Image.open(f"cubes/cube{i}.png")
	PIL_image = Image.fromarray(np.uint8(image_data * 255) , 'L')

	PIL_image.save(f"cubes/cube{i}.png","PNG")



for i in range(file_length):
	cylinder = gen.create_cylinder(m,n,rot_ax = (3e-1*np.random.rand(1,2)),noise=noise)

	max_r = cylinder.max()
	min_r = cylinder.min()
	image_data = (cylinder-min_r)/(max_r-min_r)

	PIL_image = Image.fromarray(np.uint8(image_data * 255) , 'L')

	PIL_image.save(f"cylinders/cylinder{i}.png","PNG")


