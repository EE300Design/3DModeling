import numpy as np
from stl import mesh
from PIL import Image

pi = np.pi

def polar_to_cart(M,h=1):
	m,n = M.shape
	cart = np.zeros([m,n,3])

	for i in range(m):
		for j in range(n):
			x = M[i,j]*(np.cos(2*pi/n*j)*1e-2)
			y = M[i,j]*(np.sin(2*pi/n*j)*1e-2)
			z = i*4.2e-3
			
			cart[i,j] = [x,y,z]

	return cart

temp = np.genfromtxt('test.csv',delimiter=',',dtype=float)
max_r  = temp.max()
min_r = temp.min()
range_r = max_r-min_r
PIL_image = Image.fromarray(np.uint8((temp-min_r)* 255/range_r) , 'L')
resized_Image = PIL_image.resize((200,50),Image.BILINEAR)
resized_Image.save(f"temp.png","PNG")

vertices = polar_to_cart(temp)

column_count = vertices.shape[1]
row_count = vertices.shape[0]

cylinder = mesh.Mesh(np.zeros(2*column_count*row_count, dtype=mesh.Mesh.dtype))
count = 0

for i in range(row_count-1):
	for j in range(column_count):
		cylinder.vectors[count] = [vertices[i,j-1],vertices[i,j],vertices[i+1,j-1]]
		cylinder.vectors[count+1] = [vertices[i+1,j-1],vertices[i+1,j],vertices[i,j]]
		count+=2
	
	
cylinder.save('test.stl')