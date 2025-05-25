# -*- coding: utf-8 -*-

from random import randint

T, N, X = 51, 51, 1001

def point_in_c(x, y, cx, cy, r):
    return (x-cx)**2 + (y-cy)**2 <= r**2

def c_i_c(x1, y1, r1, x2, y2, r2):
    return (x1-x2)**2 + (y1-y2)**2 < (r1+r2)**2

def invalid(x, y, r, c):
    for xi, yi, ri in c:
        if c_i_c(x, y, r, xi, yi, ri):
            return True
    return False

def gen():
    xp, yp, xt, yt, n, c = randint(0, X), randint(0, X), randint(0, X), randint(0, X), randint(0, N), []
    while xp==xt and yp == yt:
        xt, yt = randint(0, X), randint(0, X)
    for i in range(n):
        x, y, r = randint(0, X), randint(0, X), randint(1, X)
        while point_in_c(xp, yp, x, y, r) or point_in_c(xt, yt, x, y, r) or invalid(x, y, r, c):
            x, y, r = randint(0, X), randint(0, X), randint(1, X)
        c.append((x, y, r))
    return xp, yp, xt, yt, n, c

if __name__ == '__main__':
    with open('in.txt', 'w') as f:
        t = randint(1, T)
        f.write(f'{t}\n')
        for _ in range(t):
            xp, yp, xt, yt, n, c = gen()
            f.write(f'{xp} {yp} {xt} {yt}\n{n}\n')
            for p in c:
                f.write(f'{p[0]} {p[1]} {p[2]}\n')
        f.write('0 0\n')