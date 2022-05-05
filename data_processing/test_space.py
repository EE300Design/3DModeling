from stl import mesh
from mpl_toolkits import mplot3d
from matplotlib import pyplot
import numpy as np
import cylinder_generation as gen
from PIL import Image


m,n = 200,200

cube = gen.create_cube(m,n,4)

gen.mat2mesh(cube,'test.stl')
