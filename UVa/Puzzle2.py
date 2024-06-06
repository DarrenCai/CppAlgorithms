# -*- coding: utf-8 -*-

from random import random, shuffle

# N = 10000
N = 100

def check(d, n, x, y):
    if y == x+1 or (y == n and x == 1):
        return True
    for u, v in d:
        if v == u+1 or (v == n and u == 1) or u==x or u==y or v==x or v==y:
            continue
        a = x>u and x<v
        b = y>u and y<v
        if a != b:
            return True
    return False

if __name__ == '__main__':
    with open('in.txt', 'w') as f:
        f.write('10\n')
        for i in range(10):
            f.write('\n')
            n = int(random()*(N-2)) + 3
            m = int(random()*(n-2))
            f.write(f'{n}\n{m}\n')
            vetex, e, d, vis = [j for j in range(1, n+1)], [(n, 1)], [], [False for j in range((n+2)*(n+3))]
            for j in range(1, n):
                e.append((j, j+1))
            for j in range(m):
                u = int(random()*n) + 1
                v = int(random()*(n-u)) + u + 1
                while check(d, n, u, v) or vis[u*(n+1) + v]:
                    u = int(random()*n) + 1
                    v = int(random()*(n-u)) + u + 1
                vis[u*(n+1) + v] = True
                d.append((u, v))
            for j in d:
                e.append(j)
            shuffle(vetex)
            for u, v in e:
                if random() < 0.5:
                    f.write(f'{vetex[u-1]} {vetex[v-1]} ')
                else:
                    f.write(f'{vetex[v-1]} {vetex[u-1]} ')
            f.write('\n')

