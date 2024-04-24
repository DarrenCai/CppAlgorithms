# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import os

if __name__ == '__main__':
    with open('in.txt', 'r') as f:
        t = int(f.readline())
        for i in range(t):
            p, q = [], []
            for i in range(4):
                p.append([int(i) for i in f.readline().split(' ')])
            for i in range(4):
                q.append([int(i) for i in f.readline().split(' ')])
            fig = plt.figure()
            ax = fig.add_subplot(111, projection = '3d')
            style = {'alpha': 1, 'color': 'black'}
            for i in range(3):
                for j in range(i+1, 4):
                    ax.plot3D([p[i][0], p[j][0]], [p[i][1], p[j][1]], [p[i][2], p[j][2]], **style)
                    ax.plot3D([q[i][0], q[j][0]], [q[i][1], q[j][1]], [q[i][2], q[j][2]], **style)
            plt.show()