# coding=utf-8

from random import randint

def rand1():
    return randint(0, 100)

def rand2():
    return randint(20, 100)

def rand3():
    return randint(-100, 100)

def rand4():
    return randint(-100, -1)

def rand_p():
    return rand1(), rand1(), rand2()

def area(a, b, c):
    x1, y1, z1, x2, y2, z2 = b[0] - a[0], b[1] - a[1], b[2] - a[2], c[0] - a[0], c[1] - a[1], c[2] - a[2]
    return y1*z2 - y2*z1, z1*x2 - z2*x1, x1*y2 - x2*y1

def vol(a, b, c, d):
    e = area(a, b, c)
    x, y, z = d[0] - a[0], d[1] - a[1], d[2] - a[2]
    return abs(e[0]*x + e[1]*y + e[2]*z)

def gen1():
    p1, p2, p3 = rand_p(), rand_p(), rand_p()
    while area(p1, p2, p3) == (0, 0, 0):
        p1, p2, p3 = rand_p(), rand_p(), rand_p()
    p4 = rand_p()
    while vol(p1, p2, p3, p4) == 0:
        p4 = rand_p()
    n, v, p, f = randint(0, 5), vol(p1, p2, p3, p4), [p1, p2, p3, p4], []
    for _ in range(n):
        x = rand_p()
        while vol(p1, p2, p3, x) + vol(p1, p2, p4, x) + vol(p1, p3, p4, x) + vol(p2, p3, p4, x) != v:
            x = rand_p()
        f.append((x[0], x[1], x[2], randint(1, 20)))
    return n, 4, rand3(), rand3(), rand4(), f, p

def gen2():
    x1, x2, y1, y2, z1, z2 = rand1() , rand1(), rand1(), rand1(), rand2(), rand2()
    xa, xb, ya, yb, za, zb = min(x1, x2), max(x1, x2), min(y1, y2), max(y1, y2), min(z1, z2), max(z1, z2)
    n = randint(0, min((xb-xa+1)*(yb-ya+1)*(zb-za+1), 5))
    p = [(xa, ya, za), (xb, ya, za), (xb, yb, za), (xa, yb, za), (xa, ya, zb), (xb, ya, zb), (xb, yb, zb), (xa, yb, zb)]
    f = []
    for _ in range(n):
        x, y, z = rand_p()
        while x < xa or x > xb or y < ya or y > yb or z < za or z > zb:
            x, y, z = rand_p()
        f.append((x, y, z, randint(1, 20)))
    return n, 8, rand3(), rand3(), rand4(), f, p

def gen():
    if randint(0, 1) == 1:
        return gen1()
    return gen2()

if __name__ == '__main__':
    with open('in.txt', 'w') as fin:
        for _ in range(10):
            n, m, a, b, c, f, p = gen()
            fin.write(f'{n} {m} {a} {b} {c}\n')
            for v in f:
                x, y, z, r = v
                fin.write(f'{x} {y} {z} {r}\n')
            for v in p:
                x, y, z = v
                fin.write(f'{x} {y} {z}\n')
        fin.write('0 0 0 0 0\n')
