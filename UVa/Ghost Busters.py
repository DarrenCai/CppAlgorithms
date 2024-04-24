# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np

def sphere_surface_points(c, radius):
    u = np.linspace(0, 2*np.pi, 100)
    v = np.linspace(-.5*np.pi, .5*np.pi, 100)
    
    u, v = np.meshgrid(u, v)
    
    x = radius * np.cos(u) * np.cos(v) + c[0]
    y = radius * np.sin(u) * np.cos(v) + c[1]
    z = radius * np.sin(v) + c[2]

    return x, y, z

def cone_surface_points(p, v, r):
    ''' 三维空间中的旋转矩阵https://zhuanlan.zhihu.com/p/463373675 '''
    h = np.linalg.norm(v)
    v = v / h

    t = np.linspace(0, np.pi * 2, 100)
    s = np.linspace(0, 1, 100)
    t, s = np.meshgrid(t, s)

    points = np.array([r * np.cos(t) * s, r * np.sin(t) * s, h*s, np.ones((100,100))]).reshape(-1, 10000)

    axis = np.cross(np.array([0,0,1]), v)
    nx, ny, nz = axis / np.linalg.norm(axis)
    t = np.arccos(np.dot(np.array([0,0,1]), v))
    c, s = np.cos(t), np.sin(t)
    
    transform_matrix = np.array([[nx**2*(1-c)+c, nx*ny*(1-c)-nz*s, nx*nz*(1-c)+ny*s, p[0]],
                                [nx*ny*(1-c)+nz*s, ny**2*(1-c)+c, ny*nz*(1-c)-nx*s, p[1]],
                                [nx*nz*(1-c)-ny*s, ny*nz*(1-c)+nx*s, nz**2*(1-c)+c, p[2]]])
    
    return (np.dot(transform_matrix, points) + p.reshape((3,1))).reshape((3, 100, 100))

if __name__ == '__main__':
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    x, y, z = sphere_surface_points(np.array([3.6,18,27]), 3.6)
    ax.plot_surface(x, y, z, color='r', alpha=0.5)
    x, y, z = cone_surface_points(np.array([0,0,0]), np.array([4,20,30]), 4*np.sqrt(359/355))
    ax.plot_surface(x, y, z, color='yellow', alpha=.5)

    x, y, z = sphere_surface_points(np.array([33,4.4,4.4]), 4.4)
    ax.plot_surface(x, y, z, color='r', alpha=0.5)
    x, y, z = cone_surface_points(np.array([0,0,0]), np.array([37.5,5,5]), 5*np.sqrt(233/229))
    ax.plot_surface(x, y, z, color='yellow', alpha=.5)

    x, y, z = sphere_surface_points(np.array([10,5,10]), 5)
    ax.plot_surface(x, y, z, color='r', alpha=0.5)
    x, y, z = cone_surface_points(np.array([0,0,0]), np.array([20,10,20]), 30/np.sqrt(8))
    ax.plot_surface(x, y, z, color='yellow', alpha=.5)

    x, y, z = [30, 0, 0], [0, 30, 0], [0, 0, 30]
    ax.plot_trisurf(x, y, z, color='b', alpha=.5)

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    plt.show()