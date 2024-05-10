/**
 * 圆锥曲线相关
 */

#include <cmath>

#define DBL long double
#define eps 1e-12l

void ellipse_homogeneous(DBL a, DBL b, DBL t, DBL x, DBL y, DBL (&c)[6]) {
    // 根据椭圆的长短半轴、倾斜角度和中心坐标计算椭圆一般式的系数
    DBL si = sin(t), co = cos(t);
    c[0] = si/b*si/b + co/a*co/a; c[1] = 2.*(1./a/a - 1./b/b)*si*co; c[2] = co/b*co/b + si/a*si/a;
    c[3] = -2.*c[0]*x - c[1]*y; c[4] = -2.*c[2]*y - c[1]*x; c[5] = -(c[3]*x + c[4]*y)/2. - 1.;
}

void ellipse_params(DBL (&c)[6], DBL &a, DBL &b, DBL &t, DBL &x, DBL &y) {
    // 根据椭圆一般式的系数计算长短半轴、倾斜角度和中心坐标
    if (c[0] < 0) for (int i=0; i<6; ++i) c[i] = -c[i];
    DBL p = 4.*c[0]*c[2] - c[1]*c[1], q = sqrt((c[0]-c[2])*(c[0]-c[2]) + c[1]*c[1]);
    DBL r = 2.*((c[0]*c[4]*c[4] - c[1]*c[3]*c[4] + c[2]*c[3]*c[3])/p - c[5]);
    a = sqrt(r / (c[0]+c[2]-q)); b = sqrt(r / (c[0]+c[2]+q)); t = atan2(q - c[0] + c[2], c[1]);
    x = (c[1]*c[4] - 2.*c[2]*c[3]) / p; y = (c[1]*c[3] - 2.*c[0]*c[4]) / p;
}

void parabola_homogeneous(DBL x, DBL y, DBL f, DBL t, DBL (&c)[6]) {
    // 根据抛物线的顶点坐标、焦距和倾斜角度计算抛物线一般式的系数
    DBL si = sin(t), co = cos(t);
    c[0] = si*si; c[1] = -2*si*co; c[2] = co*co; c[3] = -2*c[0]*x-c[1]*y-4*f*co;
    c[4] = -2*c[2]*y-c[1]*x-4*f*si; c[5] = c[0]*x*x + c[1]*x*y + c[2]*y*y + 4*f*x*co + 4*f*y*si;
}

void parabola_params(DBL (&c)[6], DBL &x, DBL &y, DBL &f, DBL &t) {
    // 根据抛物线一般式的系数计算顶点坐标、焦距和倾斜角度
    t = atan2(2.*c[0], -c[1]);
    DBL co = cos(t), si = sin(t), s = (c[0]+c[2])*co, t = (c[0]+c[2])*si;
    f = (c[1]*c[4]-2.*c[2]*c[3]) / (8.*c[2]*s-4.*c[1]*t);
    if (f < 0.) t = atan2(-2.*c[0], c[1]), f = -f, si = -si, co = -co, s = -s, t = -t;
    DBL d1 = c[3] + 4.*f*s, e1 = c[4] + 4.*f*t; s = 4.*f*s - d1/2.; t = 4.*f*t - e1/2.;
    x = (c[1]*c[5] + d1*t) / (c[1]*s - 2*c[0]*t); y = -(2.*c[0]*x + d1) / c[1];
}

void hyperbola_homogeneous(DBL a, DBL b, DBL t, DBL x, DBL y, DBL (&c)[6]) {
    // 根据双曲线的实半轴、虚半轴、倾斜角度和中心坐标计算双曲线一般式的系数
    DBL si = sin(t), co = cos(t);
    c[0] = co/a*co/a - si/b*si/b; c[1] = 2.*(1./a/a + 1./b/b)*si*co; c[2] = si/a*si/a - co/b*co/b;
    c[3] = -(2.*c[0]*x + c[1]*y); c[4] = -(2.*c[2]*y + c[1]*x); c[5] = -(c[3]*x + c[4]*y)/2. - 1.;
}

void hyperbola_params(DBL (&c)[6], DBL &a, DBL &b, DBL &t, DBL &x, DBL &y) {
    // 根据双曲线一般式的系数计算长短半轴、倾斜角度和中心坐标
    DBL p = 4.*c[0]*c[2] - c[1]*c[1], q = sqrt((c[0]-c[2])*(c[0]-c[2]) + c[1]*c[1]);
    DBL r = 2.*((c[0]*c[4]*c[4] - c[1]*c[3]*c[4] + c[2]*c[3]*c[3])/p - c[5]);
    a = sqrt(r / (q+c[0]+c[2])), b = sqrt(r / (q-c[0]-c[2])); t = atan2(c[2]-c[0]+q, c[1]);
    x = (c[1]*c[4] - 2.*c[2]*c[3]) / p; y = (c[1]*c[3] - 2.*c[0]*c[4]) / p;
}

void cofactor(const DBL (&a)[3][3], DBL (&c)[3][3]) {
    // 计算协因数阵(cofactor matrix)
    // https://byjus.com/maths/cofactor/
    c[0][0] = a[1][1]*a[2][2] - a[1][2]*a[2][1];
    c[0][1] = a[1][2]*a[2][0] - a[1][0]*a[2][2];
    c[0][2] = a[1][0]*a[2][1] - a[1][1]*a[2][0];
    c[1][0] = a[0][2]*a[2][1] - a[0][1]*a[2][2];
    c[1][1] = a[0][0]*a[2][2] - a[0][2]*a[2][0];
    c[1][2] = a[0][1]*a[2][0] - a[0][0]*a[2][1];
    c[2][0] = a[0][1]*a[1][2] - a[0][2]*a[1][1];
    c[2][1] = a[0][2]*a[1][0] - a[0][0]*a[1][2];
    c[2][2] = a[0][0]*a[1][1] - a[0][1]*a[1][0];
}

void mul(const DBL (&a)[3][3], const DBL (&b)[3][3], DBL (&c)[3][3]) {
    c[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0];
    c[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1] + a[0][2]*b[2][1];
    c[0][2] = a[0][0]*b[0][2] + a[0][1]*b[1][2] + a[0][2]*b[2][2];
    c[1][0] = a[1][0]*b[0][0] + a[1][1]*b[1][0] + a[1][2]*b[2][0];
    c[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1];
    c[1][2] = a[1][0]*b[0][2] + a[1][1]*b[1][2] + a[1][2]*b[2][2];
    c[2][0] = a[2][0]*b[0][0] + a[2][1]*b[1][0] + a[2][2]*b[2][0];
    c[2][1] = a[2][0]*b[0][1] + a[2][1]*b[1][1] + a[2][2]*b[2][1];
    c[2][2] = a[2][0]*b[0][2] + a[2][1]*b[1][2] + a[2][2]*b[2][2];
}

DBL dot_product(const DBL (&a)[3][3], const DBL (&b)[3][3]) {
    return a[0][0]*b[0][0] + a[0][1]*b[0][1] + a[0][2]*b[0][2] +
        a[1][0]*b[1][0] + a[1][1]*b[1][1] + a[1][2]*b[1][2] + a[2][0]*b[2][0] + a[2][1]*b[2][1] + a[2][2]*b[2][2];
}

DBL det(const DBL (&a)[3][3], const DBL (&c)[3][3]) {
    // 已知方阵A和其协因数阵C，计算det|A|
    return a[0][0]*c[0][0] + a[0][1]*c[0][1] + a[0][2]*c[0][2];
}

DBL trace(const DBL (&a)[3][3], const DBL (&b)[3][3]) {
    // 计算方阵AB的迹
    // https://en.wikipedia.org/wiki/Trace_(linear_algebra)
    return a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0] +
        a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1] + a[2][0]*b[0][2] + a[2][1]*b[1][2] + a[2][2]*b[2][2];
}

DBL cubic_root(DBL x) {
    return x<0. ? -pow(-x, 1./3.) : pow(x, 1./3.);
}

DBL find_a_root(DBL a, DBL b, DBL c, DBL d) {
    // 求出一元三次方程的一个实根
    DBL A = b*b - 3*a*c, B = b*c - 9*a*d, C = c*c - 3*b*d, delta = B*B - 4.*A*C;
    if (A == 0. && B == 0.) return -c/b;
    if (delta > 0.) {
        delta = sqrt(delta);
        DBL y1 = A*b + 1.5*a*(delta-B), y2 = A*b - 1.5*a*(delta+B);
        return -(cubic_root(y1) + cubic_root(y2) + b)/3./a;
    } else if (delta > -eps) return -B/2./A;
    DBL sA = sqrt(A), t = acos((A*b-1.5*a*B)/A/sA)/3.;
    return -(b + 2*sA*cos(t)) / 3. / a;
}

int solve_quadratic_equation(DBL a, DBL b, DBL c, DBL *x) {
    // 解一元二次方程（a可以为0）并返回实根数量
    if (a == 0.) {
        if (b == 0.) return 0;
        *x = -c/b;
        return 1;
    }
    DBL delta = b*b - 4.*a*c;
    if (delta < 0.) {
        if (delta < -eps) return 0;
        delta = 0.;
    }
    a *= 2; delta = sqrt(delta);
    if (delta == 0. || delta < a*eps) {
        *x = -b/a;
        return 1;
    }
    *x = (-b-delta)/a; *(++x) = (delta-b)/a;
    return 2;
}

bool check(const DBL (&q)[3][3], DBL x, DBL y) {
    // 根据圆锥曲线的矩阵表示，检查点(x,y)是否在圆锥曲线上
    return abs(q[0][0]*x*x + 2.*q[0][1]*x*y + q[1][1]*y*y + 2.*q[0][2]*x + 2.*q[1][2]*y + q[2][2]) < eps;
}

int line_conic_intersection(const DBL (&q)[3][3], DBL a, DBL b, DBL c, DBL *x, DBL *y) {
    // 根据圆锥曲线的矩阵表示求其与直线ax+by+c=0的交点并返回交点数量（0/1/2）
    if (a == 0. && b == 0.) return 0;
    if (abs(a) > abs(b)) {
        DBL d = q[0][0]*b*b - 2.*q[0][1]*a*b + q[1][1]*a*a, f = q[0][0]*c*c - 2.*q[0][2]*a*c + q[2][2]*a*a;
        int m = solve_quadratic_equation(d, 2.*(q[1][2]*a*a + q[0][0]*b*c - q[0][1]*a*c - q[0][2]*a*b), f, y);
        for (int i=0; i<m; ++i) *(x+i) = (-c - b * (*(y+i)))/a;
        return m;
    }
    DBL d = q[0][0]*b*b - 2.*q[0][1]*a*b + q[1][1]*a*a, f = q[1][1]*c*c - 2.*q[1][2]*b*c + q[2][2]*b*b;
    int m = solve_quadratic_equation(d, 2.*(q[0][2]*b*b + q[1][1]*a*c - q[0][1]*b*c - q[1][2]*a*b), f, x);
    for (int i=0; i<m; ++i) *(x+i) = (-c - a * (*(x+i)))/b;
    return m;
}

bool check(const DBL (&q)[3][3], DBL (&x)[4], DBL (&y)[4], int m, int &n) {
    for (int i=n-1; i>=0; --i) {
        if (!check(q, x[m+i], y[m+i])) {
            if (i < n-1) x[m] = x[m+1], y[m] = y[m+1];
            --n; continue;
        }
        for (int j=0; j<m; ++j) if (abs(x[j]-x[m+i])<eps && abs(y[j]-y[m+i])<eps) {
            if (i < n-1) x[m] = x[m+1], y[m] = y[m+1];
            --n; break;
        }
    }
}

int conics_intersection(const DBL (&p)[3][3], const DBL (&q)[3][3], DBL (&x)[4], DBL (&y)[4]) {
    // 根据两圆锥曲线的矩阵表示，计算二者的交点并返回交点数量（0/1/2/3/4)
    // 即便用了long double,交点坐标的数值解其实精度仍然不高（一般小数点第3位开始就可能和解析解不一样了）
    // https://en.wikipedia.org/wiki/Matrix_representation_of_conic_sections
    // https://en.wikipedia.org/wiki/Conic_section#Intersecting_two_conics
    DBL c1[3][3], c2[3][3];
    cofactor(p, c1); cofactor(q, c2);
    DBL r = find_a_root(det(p, c1), trace(c1, q), trace(p, c2), det(q, c2));
    DBL a = r*p[0][0] + q[0][0], b = r*p[0][1] + q[0][1], c = r*p[1][1] + q[1][1],
        d = r*p[0][2] + q[0][2], e = r*p[1][2] + q[1][2], f = r*p[2][2] + q[2][2], a33 = a*c - b*b;
    if (a33 > eps) {
        x[0] = (b*e - c*d) / a33; y[0] = (b*d - a*e) / a33;
        return check(p, x[0], y[0]) && check(q, x[0], y[0]);
    } else if (a33 < -eps) {
        a33 = sqrt(-a33); c = (b*d - a*e) / a33;
        int m = line_conic_intersection(q, a, b-a33, d-c, x, y);
        check(p, x, y, 0, m);
        int n = line_conic_intersection(q, a, b+a33, d+c, x+m, y+m);
        check(p, x, y, m, n);
        return m+n;
    } else if (abs(b) < eps) {
        if (abs(a) > max(abs(c), eps)) {
            int t = solve_quadratic_equation(a, 2.*d, f, x), s = x[1];
            if (!t) return 0;
            int m = line_conic_intersection(q, -1., 0., x[0], x, y);
            check(p, x, y, 0, m);
            int n = t > 1 ? line_conic_intersection(q, -1., 0., s, x+m, y+m) : 0;
            check(p, x, y, m, n);
            return m+n;
        } else if (abs(c) > max(abs(a), eps)) {
            int t = solve_quadratic_equation(c, 2.*e, f, y), s = y[1];
            if (!t) return 0;
            int m = line_conic_intersection(q, 0., -1., y[0], x, y);
            check(p, x, y, 0, m);
            int n = t > 1 ? line_conic_intersection(q, 0., -1., s, x+m, y+m) : 0;
            check(p, x, y, m, n);
            return m+n;
        }
        int m = line_conic_intersection(q, 2.*d, 2.*e, f, x, y);
        check(p, x, y, 0, m);
        return m;
    }
    if (a < 0) a = -a, b = -b, c = -c, d = -d, e = -e, f = -f;
    DBL s = d*d - a*f;
    if (b*d*e < -eps || abs(a*e*e - c*d*d) > eps || s < -eps) return 0;
    if (s < eps) {
        int m = line_conic_intersection(q, a, b, d, x, y);
        check(p, x, y, 0, m);
        return m;
    }
    s = sqrt(s);
    int m = line_conic_intersection(q, a, b, d-s, x, y);
    check(p, x, y, 0, m);
    int n = line_conic_intersection(q, a, b, d+s, x+m, y+m);
    check(p, x, y, m, n);
    return m+n;
}