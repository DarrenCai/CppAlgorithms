/**
 * UVa1507/LA5838
 * Fuzhou 2011
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

#define eps 1e-12
#define M 502
#define sqr(x) sqrt(max(x, 0.))

struct aseg {
    double y; bool u; int s;
    bool operator< (const aseg& rhs) const {
        return y < rhs.y;
    }
} g[M<<1];

struct Point {
    double x, y;
    Point(double x = 0., double y = 0.): x(x), y(y) {}
} f[M], p[M], ch[M];
int r[M], m, n, a, b, c; double x[M*M], na, nb, nc, c1, s1, c2, s2;

typedef Point Vector;

Vector operator- (const Vector& A, const Vector& B) {
    return Vector(A.x - B.x, A.y - B.y);
}

bool operator< (const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

double Cross(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

void convert2d(Point& p) {
    int x, y, z; cin >> x >> y >> z;
    double d = x*na + y*nb + z*nc, xp = x - d*na, yp = y - d*nb, zp = z - d*nc;
    p.x = (yp*s1 + zp*c1) * s2 + xp*c2; p.y = yp*c1 - zp*s1;
}

void circle_intersect_seg(const Point& c, int r, const Point& a, const Point& b) {
    double x1 = b.x - a.x, y1 = b.y - a.y, x2 = c.x - a.x, y2 = c.y - a.y,
        s = sqrt(x1*x1 + y1*y1), d = abs(x1*y2 - x2*y1) / s;
    if (d >= r+eps) return;
    double p = (x1*x2 + y1*y2) / s; d = sqr(r*r - d*d);
    if (p-d > eps && p-d < s-eps) x[::a++] = a.x + x1*(p-d)/s;
    if (p+d > eps && p+d < s-eps) x[::a++] = a.x + x1*(p+d)/s;
}

void circle_intersect_circle(const Point& c1, int r1, const Point& c2, int r2) {
    double dx = c2.x - c1.x, dy = c2.y - c1.y, d = sqrt(dx*dx + dy*dy);
    if (d >= r1+r2+eps || d <= abs(r1-r2)-eps) return;
    double d1 = .5 * (d + (r1*r1 - r2*r2)/d), s = sqr(r1*r1-d1*d1), x0 = c1.x + dx*d1/d;
    d = dy*s/d; x[a++] = x0 - d; x[a++] = x0 + d;
}

double area(const Point& c, int r, double x1, double x2) {
    x1 -= c.x; x2 -= c.x;
    double r2 = r*r, y1 = sqr(r2 - x1*x1), y2 = sqr(r2 - x2*x2), cc = abs(x1*y2 - x2*y1);
    return .5 * (asin(cc / r2) * r2 - cc);
}

void solve() {
    double s = b*b + c*c, t = sqrt(a*a + s);
    s = sqrt(s); na = a/t; nb = b/t; nc = c/t; c1 = -c/s; s1 = -b/s; c2 = s/t; s2 = a/t;
    for (int i=0; i<n; ++i) convert2d(f[i]), cin >> r[i];
    for (int i=0; i<m; ++i) convert2d(p[i]);
    sort(p, p+m); c = 0;
    for (int i=0; i<m; ++i) {
        while (c > 1 && Cross(ch[c-1]-ch[c-2], p[i]-ch[c-2]) <= 0.) --c;
        ch[c++] = p[i];
    }
    for (int i=m-2, k=c; i>=0; --i) {
        while (c > k && Cross(ch[c-1]-ch[c-2], p[i]-ch[c-2]) <= 0.) --c;
        ch[c++] = p[i];
    }
    -- c;
    for (int i=a=0; i<c; ++i) x[a++] = ch[i].x;
    for (int i=0; i<n; ++i) {
        x[a++] = f[i].x - r[i]; x[a++] = f[i].x; x[a++] = f[i].x + r[i];
        for (int j=0; j<c; ++j) circle_intersect_seg(f[i], r[i], ch[j], ch[j+1]);
        for (int j=i+1; j<n; ++j) circle_intersect_circle(f[i], r[i], f[j], r[j]);
    }
    sort(x, x+a); s = 0.;
    for (int i=1; i<a; ++i) if (x[i] - x[i-1] > eps) {
        double v = .5 * (x[i]+x[i-1]); int t = 0;
        for (int j=0; j<c; ++j) {
            double x1 = min(ch[j].x, ch[j+1].x), x2 = max(ch[j].x, ch[j+1].x);
            if (v < x1+eps || v > x2-eps) continue;
            double u = (ch[j].x - v) / (ch[j].x - ch[j+1].x), y = u * ch[j+1].y + (1. - u) * ch[j].y;
            t ? g[t++] = {y, true, -1} : g[t++] = {y, false, -1};
        }
        for (int j=0; j<n; ++j) if (abs(v - f[j].x) < r[j]-eps) {
            double x1 = v-f[j].x, y = sqr(r[j]*r[j] - x1*x1);
            g[t++] = {f[j].y - y, false, j}; g[t++] = {f[j].y + y, true, j};
        }
        sort(g, g+t);
        for (int j=0, c=0, p; j<t; ++j) {
            if (g[j].u) {
                if (--c == 0) {
                    double y1, y2;
                    if (g[p].s >= 0) {
                        int k = g[p].s; double x1 = x[i-1]-f[k].x, x2 = x[i]-f[k].x, r2 = r[k]*r[k];
                        y1 = f[k].y - .5 * (sqr(r2-x1*x1) + sqr(r2-x2*x2));
                        s -= area(f[k], r[k], x[i-1], x[i]);
                    } else y1 = g[p].y;
                    if (g[j].s >= 0) {
                        int k = g[j].s; double x1 = x[i-1]-f[k].x, x2 = x[i]-f[k].x, r2 = r[k]*r[k];
                        y2 = f[k].y + .5 * (sqr(r2-x1*x1) + sqr(r2-x2*x2));
                        s -= area(f[k], r[k], x[i-1], x[i]);
                    } else y2 = g[j].y;
                    s -= (x[i] - x[i-1]) * (y2 - y1);
                }
            } else if (c++ == 0) p = j;
        }
    }
    cout << s / nc << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(4);
    while (cin >> n >> m >> a >> b >> c && (n || m || a || b || c)) solve();
    return 0;
}