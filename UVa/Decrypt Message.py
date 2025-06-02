# -*- coding: utf-8 -*-

from random import randint, choice

T, Q, N = 1000000008, 10, 2000

if __name__ == '__main__':
    f, primes = [False] * T, []
    for i in range(2, T):
        if not f[i]:
            print(i)
            for j in range(i*i, T, i):
                f[j] = True
            if i > 2:
                primes.append(i)

    with open("in.txt", "w") as f:
        f.write(f'{N+1}\n')
        f.write(f'{choice(primes)} {randint(2, Q)} 0\n')
        for _ in range(N):
            p, q = choice(primes), randint(2, Q)
            f.write(f'{p} {q} {randint(0, p-1)}\n')