import numpy as np
#from stl import mesh
from mpl_toolkits import mplot3d
from matplotlib import pyplot



pi = np.pi


# Note create_cylinder generates an nxm matrix where the row index is 
# porportional to the height and the column index is porportional
# to the angle

def create_cylinder(m,n,r=2,rot_ax=[1,1]):
	cylinder = np.zeros([m,n])

	for i in range(n):
		theta = 2*pi/n*i

		x = r*np.cos(theta)+rot_ax[0]
		y = r*np.sin(theta)+rot_ax[1]

		dist = (x**2+y**2)**(1/2)

		cylinder[:,i] = dist

	return cylinder



# column indexes at are assigned the faces of a cube
# within ranges of angles
def create_cube(m,n,length = 1, rot_ax = [0,0]):

	cube = np.zeros([m,n])

	for i in range(n):
		theta = 2*pi/n*i

		if(theta<pi/4 or theta>pi*7/4):
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
	m,n = M.shape
	cart = np.zeros([m,n,3])

	for i in range(m):
		for j in range(n):
			x = M[i,j]*np.cos(2*pi/n*j)
			y = M[i,j]*np.sin(2*pi/n*j)
			z = i/(m-1)*h
			
			cart[i,j] = [x,y,z]

	return cart



def mat2mesh(vertices,name= None):
	if len(vertices.shape)==2:
		vertices = polar_to_cart(vertices)

	save = (name!=None)
	column_count = vertices.shape[0]
	row_count = vertices.shape[1]

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





