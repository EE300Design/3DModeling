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

count = 0
for i in range(row_count-1):
    for j in range(column_count):
        cylinder.vectors[count] = [vertices[i,j-1],vertices[i,j],vertices[i+1,j-1]]
        cylinder.vectors[count+1] = [vertices[i+1,j-1],vertices[i+1,j],vertices[i,j]]
        count+=2

# Write the mesh to file "cube.stl"
cylinder.save('cylinder_demo.stl')

