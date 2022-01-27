import numpy as np
from stl import mesh
import math

row_count,column_count = 100,100

vertices = np.zeros([row_count,column_count,3])

for i in range(row_count):
    for j in range(column_count):

        x = math.cos(2*math.pi/column_count*j)
        y = math.sin(2*math.pi/column_count*j)
        z = 5/row_count*i
        vertices[i,j] = [x,y,z]
    

cylinder = mesh.Mesh(np.zeros(2*column_count*row_count, dtype=mesh.Mesh.dtype))

for i in range(row_count-1):
    for j in range(column_count):
        cylinder.vectors[column_count*i+j] = [vertices[i,j-1],vertices[i,j],vertices[i+1,j-1]]

half_index = (row_count-1)*column_count

for i in range(row_count-1):
    for j in range(column_count):
        cylinder.vectors[half_index+column_count*i+j] = [vertices[i+1,j-1],vertices[i+1,j],vertices[i,j]]


# Write the mesh to file "cube.stl"
cylinder.save('cylinder_demo.stl')

