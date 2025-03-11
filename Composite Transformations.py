# -*- coding: utf-8 -*-

from math import pi, floor
from random import random, choice, sample, shuffle
from decimal import Decimal, getcontext

# N = 50000
# T = 1000
N = 1000

if __name__ == '__main__':
    with open('in.txt', 'w') as f:
        n, m, t = int(random()*N)+1, int(random()*N)+1, 400
        f.write(f'{n} {m} {t}\n')
        for _ in range(n):
            f.write(f'{int(random()*N)/100} {int(random()*N)/100} {int(random()*N)/100}\n')
        for _ in range(m):
            a, b, c = int((random()-.5)*22), int((random()-.5)*22), int((random()-.5)*22)
            while a == 0 and b == 0 and c == 0:
                a, b, c = int((random()-.5)*22), int((random()-.5)*22), int((random()-.5)*22)
            f.write(f'{a} {b} {c} {int((random()-.5)*22)}\n')
        for _ in range(t):
            s = choice([0,1,2,3,4,5,6])
            if s < 3:
                f.write(f'TRANSLATE {int((random()-.5)*22)} {int((random()-.5)*22)} {int((random()-.5)*22)}\n')
            elif s < 6:
                a, b, c = int((random()-.5)*22), int((random()-.5)*22), int((random()-.5)*22)
                while a == 0 and b == 0 and c == 0:
                    a, b, c = int((random()-.5)*22), int((random()-.5)*22), int((random()-.5)*22)
                f.write(f'ROTATE {a} {b} {c} {int(random()*360)}\n')
            else:
                f.write(f'SCALE {(random()-.5)*8} {(random()-.5)*8} {(random()-.5)*8}\n')