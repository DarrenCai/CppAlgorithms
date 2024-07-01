# -*- coding: utf-8 -*-

from math import pi, floor
from random import random, choice, sample, shuffle
from decimal import Decimal, getcontext

# N = 10000
# N = 100
N = 10
W = 1000
T = 30

def gen():
    n = int(random()*N) + 1
    m = min(int(random()*(4*n+2)) + n-1, int(n*(n-1)/2))
    c, r, f, e = [0 for _ in range(n+1)], [int(random()*10)+1 for _ in range(n+1)], [i for i in range(n+1)], []

    def find(x: int):
        if x == f[x]:
            return x
        f[x] = find(f[x])
        return f[x]

    vis = [[False for _ in range(n+1)] for _ in range(n+1)]
    for j in range(m):
        u, v = int(random()*n) + 1, int(random()*n) + 1
        while u == v or c[u] > 9 or c[v] > 9 or vis[u][v]:
            u, v = int(random()*n) + 1, int(random()*n) + 1
        f[find(u)] = find(v); c[u] +=1; c[v] += 1; vis[u][v] = vis[v][u] = True
        e.append((u, v, int(random()*W)+1))
    t = find(1)
    for i in range(2, n+1):
        if find(i) != t:
            return None
    return n, m, r, e

if __name__ == '__main__':
    with open('in.txt', 'w') as f:
        f.write(f'{T}\n')
        for i in range(T):
            ret = gen()
            while not ret:
                ret = gen()
            n, m, r, e = ret
            f.write(f'{n} {m}\n')
            for j in range(1, n+1):
                f.write(f'{r[j]}\n')
            for u, v, w in e:
                f.write(f'{u} {v} {w}\n')
            f.write('\n')

