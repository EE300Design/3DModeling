from stl import mesh
import math
import numpy as np

# Create 3 faces of a cube
data = np.zeros(12, dtype=mesh.Mesh.dtype)

# Top of the cube
data['vectors'][0] = np.array([[0, 1, 1],
                                  [1, 0, 1],
                                  [0, 0, 1]])
data['vectors'][1] = np.array([[1, 0, 1],
                                  [0, 1, 1],
                                  [1, 1, 1]])
# Front back faces
data['vectors'][2] = np.array([[1, 0, 0],
                                  [1, 0, 1],
                                  [1, 1, 0]])
data['vectors'][3] = np.array([[1, 1, 1],
                                  [1, 0, 1],
                                  [1, 1, 0]])

data['vectors'][4] = np.array([[0, 0, 0],
                                  [0, 0, 1],
                                  [0, 1, 0]])
data['vectors'][5] = np.array([[0, 1, 1],
                                  [0, 0, 1],
                                  [0, 1, 0]])


# Left face
data['vectors'][6] = np.array([[0, 0, 0],
                                  [1, 0, 0],
                                  [1, 0, 1]])

data['vectors'][7] = np.array([[1, 0, 1],
                                  [0, 0, 0],
                                  [0, 0, 1]])


# Bottom
data['vectors'][8] = np.array([[0, 1, 0],
                                  [1, 0, 0],
                                  [0, 0, 0]])
data['vectors'][8] = np.array([[1, 0, 0],
                                  [0, 1, 0],
                                  [1, 1, 0]])
# Right
data['vectors'][10] = np.array([[0, 1, 0],
                                  [1, 1, 0],
                                  [1, 1, 1]])

data['vectors'][11] = np.array([[0, 1, 0],
                                  [0, 1, 1],
                                  [1, 1, 1]])



meshes = [mesh.Mesh(data.copy())]

# Optionally render the rotated cube faces
from matplotlib import pyplot
from mpl_toolkits import mplot3d

# Create a new plot
figure = pyplot.figure()
axes = mplot3d.Axes3D(figure)

# Render the cube faces
for m in meshes:
    axes.add_collection3d(mplot3d.art3d.Poly3DCollection(m.vectors))

# Auto scale to the mesh size
scale = np.concatenate([m.points for m in meshes]).flatten()
axes.auto_scale_xyz(scale, scale, scale)
axes.set_xlabel('X')
axes.set_ylabel('Y')
axes.set_zlabel('Z')

# Saving the Mesh
cube_mesh = mesh.Mesh(np.zeros(data.shape, dtype=mesh.Mesh.dtype))

cube_mesh.save('cube_demo.stl')

# Show the plot to the screen
pyplot.show()





