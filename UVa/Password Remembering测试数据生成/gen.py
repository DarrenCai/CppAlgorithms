import random

if __name__ == '__main__':
    t = 5000
    n = (1<<64) - 1
    with open('in.txt', 'w') as f:
        f.write('%d\n'%t)
        for i in range(t):
            a = random.randint(0, n)
            b = random.randint(a, n)
            f.write('%d %d\n'%(a, b))
