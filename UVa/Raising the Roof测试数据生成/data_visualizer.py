# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np

if __name__ == '__main__':
    vert = np.array([
        [69, 57, 80],
        [44, 92, 31],
        [82, 23, 39],
        [54, 54, 97],
        [70, 100, 71],
        [59, 73, 92],
        [34, 47, 88],
        [10, 93, 74]
    ])
    faces = [[vert[3], vert[0], vert[2]], [vert[6], vert[0], vert[2]], [vert[3], vert[6], vert[0]]]
    colors = ['r', 'g', 'b']

    ax = plt.figure().add_subplot(111, projection='3d')
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.view_init(elev = 90, azim = -90)

    for i, face in enumerate(faces):
        x, y, z = zip(*face)
        ax.plot_trisurf(np.array(x), np.array(y), np.array(z))

    plt.show()