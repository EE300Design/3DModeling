import numpy as np
from stl import mesh
from mpl_toolkits import mplot3d
from matplotlib import pyplot

pi = np.pi


# Note create_cylinder generates an nxm matrix where the row index is 
# porportional to the height and the column index is porportional
# to the angle

def create_cylinder(m=100,n=200,r=2,rot_ax=np.array([0,0]), noise = 0):
	# temp = np.genfromtxt('temp.csv')
	cylinder = np.zeros([m,n])

	for i in range(n):
		theta = 2*pi/n*i

		x = r*np.cos(theta)+rot_ax[0]
		y = r*np.sin(theta)+rot_ax[1]

		dist = (x**2+y**2)**(1/2)

		cylinder[:,i] = noise*np.random.rand(m)+dist

	return cylinder



# column indexes at are assigned the faces of a cube
# within ranges of angles
def create_cube(m,n,length = 1, rot_ax = np.array([0,0]),noise = 0):

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

		cube[:,i] = noise*np.random.rand(m)+((x-rot_ax[0])**2+(y-rot_ax[1])**2)**(1/2)
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
	# temp = np.genfromtxt('temp.csv')
	if len(vertices.shape)==2:
		vertices = polar_to_cart(vertices)

	column_count = vertices.shape[1]
	row_count = vertices.shape[0]

	cylinder = mesh.Mesh(np.zeros(2*column_count*row_count, dtype=mesh.Mesh.dtype))
	count = 0

	for i in range(row_count-1):
		for j in range(column_count):
			try:
				cylinder.vectors[count] = [vertices[i,j-1],vertices[i,j],vertices[i+1,j-1]]
				cylinder.vectors[count+1] = [vertices[i+1,j-1],vertices[i+1,j],vertices[i,j]]
				count+=2
			except:
				raise Exception(f'\ni = {i}\nj = {j}')
	
	if name!=None:
		cylinder.save(name)
	return cylinder


test = create_cylinder(50,200)
mat2mesh(test,'test.stl')
np.savetxt('test.csv',test,delimiter=',')
