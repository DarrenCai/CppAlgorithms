# coding=utf-8

from random import randint

# X, N = 100000, 25
X, N = 12, 4

def out(p, x, y):
    for i in range(0, len(x), 2):
        if p[0] >= x[i] and p[0] <= x[i+1]:
            return False
    for i in range(0, len(y), 2):
        if p[1] >= y[i] and p[1] <= y[i+1]:
            return False
    return True

def gen():
    n, m, y, x = randint(1, N), randint(1, N), [], []
    for i in range(2*n):
        f = True
        while f:
            f = False
            v = randint(-X, X)
            for j in range(i):
                if y[j] == v:
                    f = True
                    break
            if not f:
                y.append(v)
    for i in range(2*m):
        f = True
        while f:
            f = False
            v = randint(-X, X)
            for j in range(i):
                if x[j] == v:
                    f = True
                    break
            if not f:
                x.append(v)
    y.sort()
    x.sort()
    s, t = (randint(-X, X), randint(-X, X)), (randint(-X, X), randint(-X, X))
    while out(s, x, y):
        s = (randint(-X, X), randint(-X, X))
    while out(t, x, y):
        t = (randint(-X, X), randint(-X, X))
    return n, m, s, t, y, x

if __name__ == '__main__':
    with open('in.txt', 'w') as f:
        for _ in range(10):
            n, m, s, t, y, x = gen()
            f.write(f'{n} {m}\n{s[0]} {s[1]} {t[0]} {t[1]}\n{y[0]}')
            for i in range(1, 2*n):
                f.write(f' {y[i]}')
            f.write(f'\n{x[0]}')
            for i in range(1, 2*m):
                f.write(f' {x[i]}')
            f.write(f'\n')
        f.write('0 0\n')
