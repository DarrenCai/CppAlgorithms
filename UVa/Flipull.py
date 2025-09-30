# -*- coding: utf-8 -*-

from random import randint, choice, sample

ch = 'TO#XM'

if __name__ == '__main__':
    with open('in.txt', 'w') as f:
        for i in range(50):
            n, b = randint(4, 6), randint(0, 3)
            if b < 3:
                b = randint(3, n)
            else:
                b = randint(n+1, n*n-1)
            f.write(f'{n} {b} {choice(ch)}\nGame{i+1}\n')
            for _ in range(n):
                for _ in range(n):
                    f.write(f'{ch[randint(0,3)]}')
                f.write('\n')
            for i in range(1, n+1):
                if randint(1, 6) == 6:
                    f.write('X ')
                else:
                    f.write(f'r{i} ')
            for _ in range(n+1, 13):
                if randint(1, 6) == 6:
                    f.write('X ')
                else:
                    f.write(f'c{randint(1, n)} ')
            f.write('\n')
        f.write('0\n')