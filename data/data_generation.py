from stl import mesh
from mpl_toolkits import mplot3d
from matplotlib import pyplot
import numpy as np
import cylinder_generation as gen
from PIL import Image


m,n = 300,300

file_length = 100

for i in range(file_length):
	r = 15+2*np.random.random()
	rot = np.random.random_sample((2,))*.25
	cube = gen.create_cube(n,m,rot_ax=rot)

	max_r = cube.max()
	min_r = cube.min()
	image_data = (cube-min_r)/(max_r-min_r)

	PIL_image = Image.fromarray(np.uint8(image_data * 255) , 'L')
	PIL_image.save('cubes/cube'+str(i)+'.png')



for i in range(file_length):
	r = 5+5*np.random.random()
	rot = np.random.random_sample((2,))*.5
	cylinder = gen.create_cylinder(n,m,rot_ax=rot)

	max_r = cylinder.max()
	min_r = cylinder.min()
	image_data = (cylinder-min_r)/(max_r-min_r)

	PIL_image = Image.fromarray(np.uint8(image_data * 255) , 'L')

	PIL_image.save('cylinders/cylinder'+str(i)+'.png')
PIL_image.show()

# gradient between 0 and 1 for 256*256
# array = np.linspace(0,1,256*256)
# # reshape to 2d
# mat = np.reshape(array,(256,256))
# # Creates PIL image
# img = Image.fromarray(np.uint8(image_data * 255) , 'L')
# img.show()