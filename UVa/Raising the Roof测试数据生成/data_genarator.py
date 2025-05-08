# -*- coding: utf-8 -*-

from random import sample, randint
from fractions import Fraction as frac

X, V, T, C = 100, 10, 15, 10
# X, V, T, C = 100, 5, 7, 300

def gen_point(p):
    while True:
        x, y, z, ok = randint(1, X), randint(1, X), randint(1, X), True
        for xi, yi, zi in p:
            if xi == x and yi == y and zi == z:
                ok = False
                break
        if ok:
            return x, y, z
        
def cross(v1, v2):
    return (v1[1]*v2[2] - v1[2]*v2[1], v1[2]*v2[0] - v1[0]*v2[2], v1[0]*v2[1] - v1[1]*v2[0])

def dot(v1, v2):
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]

def sub(v1, v2):
    return (v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2])

def solve_equations(a1, b1, c1, a2, b2, c2):
    '''a1*x + b1*y = c1'''
    '''a2*x + b2*y = c2'''
    p = a1*b2 - a2*b1
    return frac(b2*c1 - b1*c2, p), frac(a1*c2 - a2*c1, p)

def line_intersect_seg(p, n, a, b):
    v1, v2 = sub(p, a), sub(b, a)
    x, y, z = cross(n, v2)
    if x == 0 and y == 0 and z == 0:
        x, y, z = cross(v1, v2)
        return [a, b] if x == 0 and y == 0 and z == 0 else []
    s = (x**2 + y**2 + z**2)**.5
    x, y, z = cross(n, v1)
    s = (x**2 + y**2 + z**2)**.5 / s
    if s >= 0. and s <= 1.: ### eps?
        return [(a[0] + v2[0]*s, a[1] + v2[1]*s, a[2] + v2[2]*s)]
    else:
        return []

def line_intersect_tri(p, n, a, b, c):
    q = line_intersect_seg(p, n, a, b)
    for x in line_intersect_seg(p, n, a, c):
        q.append(x)
    for x in line_intersect_seg(p, n, b, c):
        q.append(x)
    if len(q) == 0:
        return []
    q.sort(key = lambda x: dot(sub(x, p), n))
    x0, x1 = q[0], q[-1]
    return [x0] if x0[0] == x1[0] and x0[1] == x1[1] and x0[2] == x1[2] else [x0, x1]

def line_intvs_intersect(a, b, intv):
    v, d = sub(b, a), []
    s = v[0]**2 + v[1]**2 + v[2]**2
    for x in intv:
        d.append(dot(sub(x, a), v) / s)
    d.sort()
    s0, s1 = max(0., d[0]), min(1., d[-1])
    if s0 > s1:
        return []
    return [(a[0] + v[0]*s0, a[1] + v[1]*s0, a[2] + v[2]*s0), (a[0] + v[0]*s1, a[1] + v[1]*s1, a[2] + v[2]*s1)]

def point_in_tri(p, a, b, c):
    c1, c2, c3 = cross(sub(b, a), sub(p, a)), cross(sub(c, b), sub(p, b)), cross(sub(a, c), sub(p, c))
    return dot(c1, c2) > 0 and dot(c2, c3) > 0 and dot(c3, c1) > 0

def seg_cross_seg(a, b, c, d, ec = False):
    v1, v2, v3 = sub(b, a), sub(d, c), sub(c, a)
    c1, c2, c3 = cross(v1, v2), cross(v3, v2), cross(v3, v1)
    if c1[0] == 0 and c1[1] == 0 and c1[2] == 0:
        return False
    l1 = (c1[0]**2 + c1[1]**2 + c1[2]**2)**.5
    l2, l3 = (c2[0]**2 + c2[1]**2 + c2[2]**2)**.5 / l1, (c3[0]**2 + c3[1]**2 + c3[2]**2)**.5 / l1
    if l2 < 0. or l2 > 1.: ### eps?
        return False
    return l3 >= 0. and l3 <= 1. if ec else l3 > 0. and l3 < 1.

def seg_cross_tri(a, b, c, d, e):
    if seg_cross_seg(a, b, c, d):
        return seg_cross_seg(a, b, c, e, True) or seg_cross_seg(a, b, d, e, True)
    if seg_cross_seg(a, b, c, e):
        return seg_cross_seg(a, b, c, d, True) or seg_cross_seg(a, b, d, e, True)
    if seg_cross_seg(a, b, d, e):
        return seg_cross_seg(a, b, c, d, True) or seg_cross_seg(a, b, c, e, True)
    return False

def valid(t1, t2):
    v1, v2, v3, v4 = sub(t1[1], t1[0]), sub(t1[2], t1[0]), sub(t2[1], t2[0]), sub(t2[2], t2[0])
    n1, n2 = cross(v1, v2), cross(v3, v4)
    if n1[0] == 0 and n1[1] == 0 and n1[2] == 0:
        return False
    cc, d1 = cross(n1, n2), dot(n1, t1[0])
    if cc[0] == 0 and cc[1] == 0 and cc[2] == 0:
        if dot(n1, t2[0]) != d1:
            return True
        for p in t1:
            if point_in_tri(p, t2[0], t2[1], t2[2]):
                return False
        for p in t2:
            if point_in_tri(p, t1[0], t1[1], t1[2]):
                return False
        for i in range(1, 3):
            for j in range(i):
                if seg_cross_tri(t1[i], t1[j], t2[0], t2[1], t2[2]) or seg_cross_tri(t2[i], t2[j], t1[0], t1[1], t1[2]):
                    return False
        return True
    else:
        x, y, z, d2 = 1, 1, 1, dot(n2, t2[0])
        if cc[0] != 0:
            y, z = solve_equations(n1[1], n1[2], d1 - n1[0]*x, n2[1], n2[2], d2 - n2[0]*x)
        elif cc[1] != 0:
            x, z = solve_equations(n1[0], n1[2], d1 - n1[1]*y, n2[0], n2[2], d2 - n2[1]*y)
        else:
            x, y = solve_equations(n1[0], n1[1], d1 - n1[2]*z, n2[0], n2[1], d2 - n2[2]*z)
        q1, q2 = line_intersect_tri((x, y, z), cc, t1[0], t1[1], t1[2]), line_intersect_tri((x, y, z), cc, t2[0], t2[1], t2[2])
        if len(q1) * len(q2) < 2:
            return True
        q = line_intvs_intersect(q1[0], q1[1], q2) if len(q1) > 1 else line_intvs_intersect(q2[0], q2[1], q1)
        if len(q) == 0:
            return True
        p = ((q[0][0]+q[-1][0]) / 2, (q[0][1]+q[-1][1]) / 2, (q[0][2]+q[-1][2]) / 2)
        return not (point_in_tri(p, t1[0], t1[1], t1[2]) or point_in_tri(p, t2[0], t2[1], t2[2]))

def gen_tri(p, t):
    while True:
        s, ok = sample([i for i in range(len(p))], 3), True
        tc, ts = (p[s[0]], p[s[1]], p[s[2]]), sorted(s)
        for ti in t:
            tt = sorted(ti)
            if (ts[0] == tt[0] and ts[1] == tt[1] and ts[2] == tt[2]) or not valid((p[ti[0]], p[ti[1]], p[ti[2]]), tc):
                ok = False
                break
        if ok:
            return s

def gen():
    n, p, t = randint(3, V), [], []
    for _ in range(n):
        p.append(gen_point(p))
    m = randint(1, min(n*(n-1)*(n-2)//6, T))
    for _ in range(m):
        t.append(gen_tri(p, t))
    return n, m, p, t

if __name__ == '__main__':
    with open('in.txt', 'w') as f:
        for _ in range(C):
            n, m, v, t = gen()
            f.write(f'{n} {m}\n')
            for p in v:
                f.write(f'{p[0]} {p[1]} {p[2]}\n')
            for p in t:
                f.write(f'{p[0]+1} {p[1]+1} {p[2]+1}\n')
        f.write('0 0\n')