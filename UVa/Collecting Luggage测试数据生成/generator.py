# -*- coding: utf-8 -*-

from random import randint
from functools import cmp_to_key

T, N, X, V = 10, 8, 100, 1000

xs, ys, flt_max, flt_min = 0, 0, float('inf'), float('-inf')

def gen_point():
    return randint(-X, X), randint(-X, X)

def slope(p):
    x, y = p
    if x == xs:
        return flt_max if y > ys else flt_min
    return (y-ys) / (x-xs)

def cmp(pa, pb):
    s1, s2 = slope(pa), slope(pb)
    if s1 < s2:
        return -1
    if s1 > s2:
        return 1
    da, db = (pa[0]-xs)**2 + (pa[1]-ys)**2, (pb[0]-xs)**2 + (pb[1]-ys)**2
    if da < db:
        return -1
    if da > db:
        return 1
    return 0

def invalid(x, y, poly):
    wn, n = 0, len(poly)
    for i in range(n):
        j = i+1 if i+1 < n else 0
        xi, yi = poly[i]
        xj, yj = poly[j]
        dx, dy, vx, vy = xj-xi, yj-yi, x-xi, y-yi
        c, d, e = dx*vy - dy*vx, vx*dx + vy*dy, dx*dx + dy*dy
        if c == 0 and d >= 0 and d <= e:
            return True
        d1, d2 = yi-y, yj-y
        if c > 0 and d1 <= 0 and d2 > 0:
            wn += 1
        if c < 0 and d2 <= 0 and d1 > 0:
            wn -= 1
    return wn != 0

def gen():
    global xs, ys
    n, p, s = randint(3, N), [], -1
    for i in range(n):
        x, y = gen_point()
        while True:
            ok = True
            for j in range(i):
                xj, yj = p[j]
                if x == xj and y == yj:
                    ok = False
                    break
            if ok:
                break
            x, y = gen_point()
        p.append((x, y))
        if s < 0 or p[i][0] < p[s][0] or (p[i][0] == p[s][0] and p[i][1] < p[s][1]):
            s = i
    xs, ys = p[s]
    p.sort(key=cmp_to_key(cmp))
    vx, vy, q = p[-1][0] - p[0][0], p[-1][1] - p[0][1], [p[-1]]
    d = vx*vx + vy*vy
    for i in range(2, n):
        dx, dy = p[-i][0] - p[0][0], p[-i][1] - p[0][1]
        if vx*dy - vy*dx != 0:
            break
        e = vx*dx + vy*dy
        if e < 0 or e > d:
            break
        q.append(p[-i])
    q.reverse()
    for i in range(len(q)):
        p[-(i+1)] = q[i]
    xp, yp = gen_point()
    while invalid(xp, yp, p):
        xp, yp = gen_point()
    vl = randint(1, V-1)
    return n, p, xp, yp, vl, randint(vl, V)

def test():
    from random import shuffle
    p = [(0,0), (1,-1), (2,-2), (3,-3), (4,-2), (6,-3), (6,3), (4,2), (2,1)]
    shuffle(p)
    print(p)

    global xs, ys
    s, n = -1, len(p)
    for i in range(n):
        x, y = p[i]
        if s < 0 or x < p[s][0] or (x == p[s][0] and y < p[s][1]):
            s = i
    xs, ys = p[s]
    p.sort(key=cmp_to_key(cmp))

    print(p)

    vx, vy, q = p[-1][0] - p[0][0], p[-1][1] - p[0][1], [p[-1]]
    d = vx*vx + vy*vy
    for i in range(2, n):
        dx, dy = p[-i][0] - p[0][0], p[-i][1] - p[0][1]
        if vx*dy - vy*dx != 0:
            break
        e = vx*dx + vy*dy
        if e < 0 or e > d:
            break
        q.append(p[-i])
    q.reverse()
    for i in range(len(q)):
        p[-(i+1)] = q[i]

    print(p)

if __name__ == '__main__':
    test()
    with open('in.txt', 'w') as f:
        for i in range(T):
            n, p, xp, yp, vl, vp = gen()
            f.write(f'{n}\n')
            for x, y in p:
                f.write(f'{x} {y}\n')
            f.write(f'{xp} {yp}\n')
            f.write(f'{vl} {vp}\n\n')
        f.write('0\n')