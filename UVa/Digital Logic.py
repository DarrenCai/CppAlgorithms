# -*- coding: utf-8 -*-

from random import randint, choice, sample

if __name__ == '__main__':
    with open('in.txt', 'w') as f:
        for _ in range(2000):
            n = randint(1, 5)
            s, g, cc, t = randint(n, 10), [], [], 0
            for i in range(n):
                a, b, c, ok = randint(0, 1), randint(0, 1), randint(0, 1), False
                while not ok:
                    a, b, c = randint(0, 1), randint(0, 1), randint(0, 1)
                    ok = not ((a==1 and b==1 and c==1) or (a==0 and b==0 and c==0))
                    for j in range(i):
                        m = g[j][0]
                        ai, bi, ci = g[j][1]
                        if a == ai and b == bi and c == ci:
                            ok = False
                            break
                m = randint(1, s-t-(n-1-i))
                t += m
                cc.append(m)
                g.append((m, [a, b, c]))
            k, ina, inb = [i for i in range(t)], [i for i in range(t)], [i for i in range(t)]
            for i in range(t):
                s = []
                for j in range(n):
                    if cc[j] > 0:
                        s.append(j)
                v = choice(s)
                cc[v] -= 1
                k[i], ina[i], inb[i] = v, choice([x for x in range(i+4)]), choice([x for x in range(i+4)])
            f.write(f'{n}\n')
            for i in range(n):
                m = g[i][0]
                a, b, c = g[i][1]
                cc.append(c)
                f.write(f'{m} {a} {b} {c}\n')
            out, vis = [], [False] * (t+4)
            for i in range(t):
                vis[ina[i]] = vis[inb[i]] = True
            for i in range(t):
                if not vis[i+4]:
                    out.append(i+4)
            if randint(0, 1) == 1 and len(out) == 1:
                out = [t+3, t+3, t+3, t+3]
            elif len(out) < 4:
                for i in sample([x for x in range(t+4)], 4-len(out)):
                    out.append(i)
            p = randint(0, 15)
            a, b, c, d = p>>3, (p>>2)&1, (p>>1)&1, p&1
            v = [x for x in range(t+4)]
            for x in range(16):
                v[0], v[1], v[2], v[3] = x>>3, (x>>2)&1, (x>>1)&1, x&1
                for i in range(t):
                    v[i+4] = g[k[i]][1][v[ina[i]]+v[inb[i]]]
                f.write(f'{v[out[a]]<<3 | v[out[b]]<<2 | v[out[c]]<<1 | v[out[d]]} ')
            f.write('\n')
        f.write('0\n')