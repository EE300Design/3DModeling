import numpy as np
from stl import mesh
from mpl_toolkits import mplot3d
from matplotlib import pyplot


pi = np.pi
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

temp = np.genfromtxt('test.csv',delimiter=',',dtype=float)

vertices = polar_to_cart(temp)

column_count = vertices.shape[0]
row_count = vertices.shape[1]

cylinder = mesh.Mesh(np.zeros(2*column_count*row_count, dtype=mesh.Mesh.dtype))
count = 0

for i in range(row_count-1):
	for j in range(column_count):
		cylinder.vectors[count] = [vertices[i,j-1],vertices[i,j],vertices[i+1,j-1]]
		cylinder.vectors[count+1] = [vertices[i+1,j-1],vertices[i+1,j],vertices[i,j]]
		count+=2
	
cylinder.save('test.stl')

