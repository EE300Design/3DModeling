import numpy as np
from stl import mesh
from mpl_toolkits import mplot3d
from matplotlib import pyplot
import math

# Note create_cylinder generates an nxm matrix where the row index is 
# porportional to the height and the column index is porportional
# to the angle

def create_cylinder(n,m,radius=1,rot_ax=[0,0]):
	cylndr = np.zeros([n,m])
	for i in range(n):
		for j in range(m):
			x = radius*math.cos(2*math.pi/n*j)
			y = radius*math.sin(2*math.pi/m*j)

			r = ((rot_ax[0]-x)**2+(rot_ax[1]-y)**2)**(1/2)
			cylndr[i,j] = r

	return cylndr


def polar_to_cartesian(M,h=1):

	n,m = M.shape
	cart = mp.zeros([n,m,3])

	for i in range(n):
		for j in range(m):
			x = M[i,j]*math.cos(2*math.pi/m*j)
			y = M[i,j]*math.sin(2*math.pi/m*j)

			z = 5/height*i
			cart[i,j] = [x,y,z]

	return cart

# def save_stl():



# def view_stl():
