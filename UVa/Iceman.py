from random import random, sample, choice

N, K, P = 10, 5, 2

def sel_dest(s, m, n):
    p = []
    for i in range(1, n-1):
        for j in range(1, m-1):
            if s[i*m+j] == '.' and s[(i+1)*m+j] == 'X':
                p.append(i*m+j)
    if len(p) > 0:
        return choice(p)
    return -1

def sel_start(s, m, n):
    p = []
    for i in range(1, n-1):
        for j in range(1, m-1):
            if s[i*m+j] == '.':
                p.append(i*m+j)
    if len(p) > 0:
        return choice(p)
    return -1

def gen():
    m, n, p = int(random()*N)+1, int(random()*N)+1, []
    s, a, b = ['X' for _ in range(m*n)], -1, -1
    for i in range(1, n-1):
        for j in range(1, m-1):
            p.append(i*m+j)
            s[i*m+j] = '.'
    if m > 2 and n > 2:
        for k in sample(p, int(random()*(m-2)*(n-2))):
            s[k] = 'X'
        if int(random()*K) > 0:
            b = sel_dest(s, m, n)
            if b > 0:
                s[b] = '#'
        if int(random()*K) > 0:
            a = sel_start(s, m, n)
            if a > 0:
                s[a] = '@'
        for i in range(1, n-1):
            for j in range(1, m-1):
                k = i*m+j
                if s[k] == '.' and int(random()*P) > 0:
                    l, r, cl, cr = False, False, s[k-1], s[k+1]
                    if cl == 'X' or cl == 'O' or cl == ']':
                        if cl == 'O':
                            s[k-1] = '['
                        elif cl == ']':
                            s[k-1] = '='
                        l = True
                    if cr == 'X' or cr == 'O' or cr == '[':
                        if cr == 'O':
                            s[k+1] = ']'
                        elif cr == '[':
                            s[k+1] = '='
                        r = True
                    if l:
                        s[k] = '=' if r else ']'
                    else:
                        s[k] = '[' if r else 'O'
    return s, m, n

if __name__ == '__main__':
    with open('in.txt', 'w') as f:
        for _ in range(600):
            s, m, n = gen()
            f.write(f'{n} {m}\n')
            for i in range(n):
                for j in range(m):
                    f.write(s[i*m+j])
                f.write('\n')
        f.write('0\n')