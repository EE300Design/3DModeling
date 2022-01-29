import numpy as np
from stl import mesh
from mpl_toolkits import mplot3d
from matplotlib import pyplot



pi = np.pi


# Note create_cylinder generates an nxm matrix where the row index is 
# porportional to the height and the column index is porportional
# to the angle

def create_cylinder(m,n,radius=1,rot_ax=[0,0]):
	cylndr = np.zeros([n,m])
	for i in range(n):
		theta = 2*pi/n*i
		x = radius*np.cos(theta)
		y = radius*np.sin(theta)

		cylndr[:,i] = ((x-rot_ax[0])**2+(y-rot_ax[1])**2)**(1/2)
	return cylndr



# column indexes at are assigned the faces of a cube
# within ranges of angles
def create_cube(m,n,length = 1, rot_ax = [0,0]):

	cube = np.zeros([n,m])

	for i in range(m):
		theta = 2*pi/n*i

		if(theta<pi/4 | theta>pi*7/4):
			x = length
			y = length*np.tan(theta)

		elif(theta<3*pi/4):
			y = length
			x = -length*np.tan(theta-pi/2)

		elif theta<5*pi/4:
			x = -length
			y = -length*np.tan(theta-pi)

		elif theta<7*pi/4:
			x = length*np.tan(theta-3*pi/2)
			y = -length

		cube[:,i] = ((x-rot_ax[0])**2+(y-rot_ax[1])**2)**(1/2)
	return cube


# converts these particular matrixes
# to the dot nets in 3D space

def polar_to_cart(M,h=1):
	n,m = M.shape
	cart = mp.zeros([n,m,3])

	for i in range(n):
		for j in range(m):
			x = M[i,j]*np.cos(2*pi/m*j)
			y = M[i,j]*np.sin(2*pi/m*j)
			z = i/n*height
			
			cart[i,j] = [x,y,z]

	return cart



def dot_mat_2mesh(vertices,name='test.stl',save=False):

	cylinder = mesh.Mesh(np.zeros(2*column_count*row_count, dtype=mesh.Mesh.dtype))
	count = 0

	for i in range(row_count-1):
		for j in range(column_count):
			cylinder.vectors[count] = [vertices[i,j-1],vertices[i,j],vertices[i+1,j-1]]
			cylinder.vectors[count+1] = [vertices[i+1,j-1],vertices[i+1,j],vertices[i,j]]
			count+=2
	
	if save:
		cylinder.save(name)
	return cylinder





