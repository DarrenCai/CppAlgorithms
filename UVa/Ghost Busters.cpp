/**
 * UVa1313/LA2693
 * NEERC 2002
 */

#include <iostream>
#include <cmath>
using namespace std;

#define eps 1e-12l
#define N 102
#define DBL long double
DBL h[N][6], px[2*N*N], py[2*N*N], x[4], y[4], q = 0.5773502691896257, s = 0.816496580927726; int g[N], p[N], c, n, t;

void cofactor(const DBL (&a)[3][3], DBL (&c)[3][3]) {
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

DBL det(const DBL (&a)[3][3], const DBL (&c)[3][3]) {
    return a[0][0]*c[0][0] + a[0][1]*c[0][1] + a[0][2]*c[0][2];
}

DBL trace(const DBL (&a)[3][3], const DBL (&b)[3][3]) {
    return a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0] +
        a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1] + a[2][0]*b[0][2] + a[2][1]*b[1][2] + a[2][2]*b[2][2];
}

DBL cubic_root(DBL x) {
    return x<0. ? -pow(-x, 1./3.) : pow(x, 1./3.);
}

DBL find_a_root(DBL a, DBL b, DBL c, DBL d) {
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
    return abs(q[0][0]*x*x + 2.*q[0][1]*x*y + q[1][1]*y*y + 2.*q[0][2]*x + 2.*q[1][2]*y + q[2][2]) < eps;
}

int line_conic_intersection(const DBL (&q)[3][3], DBL a, DBL b, DBL c, DBL *x, DBL *y) {
    if (a == 0. && b == 0.) return 0;
    if (abs(a) > abs(b)) {
        DBL d = q[0][0]*b*b - 2.*q[0][1]*a*b + q[1][1]*a*a, f = q[0][0]*c*c - 2.*q[0][2]*a*c + q[2][2]*a*a;
        int m = solve_quadratic_equation(d, 2.*(q[1][2]*a*a + q[0][0]*b*c - q[0][1]*a*c - q[0][2]*a*b), f, y);
        for (int i=0; i<m; ++i) *(x+i) = (-c - b * (*(y+i)))/a;
        return m;
    }
    DBL d = q[0][0]*b*b - 2.*q[0][1]*a*b + q[1][1]*a*a, f = q[1][1]*c*c - 2.*q[1][2]*b*c + q[2][2]*b*b;
    int m = solve_quadratic_equation(d, 2.*(q[0][2]*b*b + q[1][1]*a*c - q[0][1]*b*c - q[1][2]*a*b), f, x);
    for (int i=0; i<m; ++i) *(y+i) = (-c - a * (*(x+i)))/b;
    return m;
}

void check(const DBL (&q)[3][3], DBL (&x)[4], DBL (&y)[4], int m, int &n) {
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
            int t = solve_quadratic_equation(a, 2.*d, f, x); double s = x[1];
            if (!t) return 0;
            int m = line_conic_intersection(q, -1., 0., x[0], x, y);
            check(p, x, y, 0, m);
            int n = t > 1 ? line_conic_intersection(q, -1., 0., s, x+m, y+m) : 0;
            check(p, x, y, m, n);
            return m+n;
        } else if (abs(c) > max(abs(a), eps)) {
            int t = solve_quadratic_equation(c, 2.*e, f, y); double s = y[1];
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

bool check(const DBL (&h)[6], DBL x, DBL y) {
    return h[0]*x*x + h[1]*x*y + h[2]*y*y + h[3]*x + h[4]*y + h[5] < eps;
}

void solve() {
    cin >> n; t = 0;
    for (int i=1; i<=n; ++i) {
        DBL x, y, z; int r; cin >> x >> y >> z >> r;
        DBL v = x; x = (v-y)*M_SQRT1_2; v = (v+y)*M_SQRT1_2; y = q*v - s*z; z = s*v + q*z;
        DBL co = r / sqrt(x*x+y*y+z*z), si = sqrt(1. - co*co);
        if (z != 10.) v = 10. / z, x *= v, y *= v, v = sqrt(x*x + y*y);
        DBL l = sqrt(v*v + 100.), sinb = v / l, cosb = sqrt(1 - sinb*sinb);
        DBL c = 1./(si*cosb+sinb*co), d = 1./(si*cosb-sinb*co);
        double a = .5*l*co*(c + d), b = a/si/sqrt(c*d);
        if (v > 0.) d = (a-l*co*c+v)/v, x *= d, y *= d;
        l = sqrt(x*x + y*y); si = y/l; co = x/l; px[t] = x, py[t++] = y;
        h[i][0] = si/b*si/b + co/a*co/a; h[i][1] = 2.*(1./a/a - 1./b/b)*si*co;
        h[i][2] = co/b*co/b + si/a*si/a; h[i][3] = -2.*h[i][0]*x - h[i][1]*y;
        h[i][4] = -2.*h[i][2]*y - h[i][1]*x; h[i][5] = -(h[i][3]*x + h[i][4]*y)/2. - 1.;
    }
    for (int i=1; i<n; ++i) {
        DBL p[][3] = {{h[i][0], h[i][1]/2., h[i][3]/2.},
            {h[i][1]/2., h[i][2], h[i][4]/2.}, {h[i][3]/2., h[i][4]/2., h[i][5]}};
        for (int j=i+1; j<=n; ++j) {
            DBL q[][3] = {{h[j][0], h[j][1]/2., h[j][3]/2.},
                {h[j][1]/2., h[j][2], h[j][4]/2.}, {h[j][3]/2., h[j][4]/2., h[j][5]}};
            for (int k = conics_intersection(p, q, x, y)-1; k>=0; --k) px[t] = x[k], py[t++] = y[k];
        }
    }
    c = 0;
    for (int i=0; i<t; ++i) {
        int cc = 0;
        for (int j=1; j<=n; ++j) if (check(h[j], px[i], py[i])) p[cc++] = j;
        if (cc > c) {
            c = cc;
            for (int j=0; j<cc; ++j) g[j] = p[j];
        }
    }
    cout << c;
    if (c > 0) cout << endl << g[0];
    for (int i=1; i<c; ++i) cout << ' ' << g[i];
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int k=0; k<t; ++k) {
        if (k) cout << endl;
        solve();
    }
    return 0;
}