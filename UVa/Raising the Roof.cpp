/**
 * UVa1065/LA3809
 * 可见的屋顶
 * World Finals >> 2007 - Tokyo
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;

#define eps 1e-9
#define V 302
#define T 1005
int x[V], y[V], z[V], idx[T][3], a[T], b[T], c[T], d[T], e[T], q[T], v, t, m, n, kase = 0; double f[T], g[3*T*T];
struct seg {
    double y1, y2;
    bool operator< (const seg& rhs) const {
        return y1 + y2 < rhs.y1 + rhs.y2;
    }
} s[T<<1];

void calc_tri_params(int (&i)[3], int j) {
    cin >> i[0] >> i[1] >> i[2]; --i[0]; --i[1]; --i[2];
    int x0 = x[i[0]], y0 = y[i[0]], z0 = z[i[0]], x1 = x[i[1]] - x0, y1 = y[i[1]] - y0, z1 = z[i[1]] - z0,
        x2 = x[i[2]] - x0, y2 = y[i[2]] - y0, z2 = z[i[2]] - z0;
    a[j] = y1*z2 - y2*z1; b[j] = z1*x2-z2*x1; c[j] = x1*y2-x2*y1;
    if (c[j] == 0) return;
    d[j] = a[j]*x0+b[j]*y0+c[j]*z0; e[m++] = j; f[j] = sqrt(a[j]*a[j] + b[j]*b[j] + c[j]*c[j]) / abs(c[j]);
}

void seg_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    int c = (x4-x3)*(y2-y1) - (y4-y3)*(x2-x1), t1 = (y4-y3)*(x1-x3)-(x4-x3)*(y1-y3), t2 = (y2-y1)*(x1-x3)-(x2-x1)*(y1-y3);
    if (c == 0 || (c > 0 && (t1 <= 0 || t1 >= c || t2 <= 0 || t2 >= c))
        || (c < 0 && (t1 >= 0 || t1 <= c || t2 >= 0 || t2 <= c))) return;
    g[n++] = x1 + (x2-x1)*t1 / double(c);
}

void tri_intersect(int i, int j) {
    int t1[][2] = {{x[idx[i][0]], y[idx[i][0]]}, {x[idx[i][1]], y[idx[i][1]]}, {x[idx[i][2]], y[idx[i][2]]}},
        t2[][2] = {{x[idx[j][0]], y[idx[j][0]]}, {x[idx[j][1]], y[idx[j][1]]}, {x[idx[j][2]], y[idx[j][2]]}};
    for (int k=0; k<3; ++k) for (int n = k<2 ? k+1 : 0, m=0; m<3; ++m)
        seg_intersect(t1[k][0], t1[k][1], t1[n][0], t1[n][1], t2[m][0], t2[m][1], t2[m<2 ? m+1:0][0], t2[m<2 ? m+1:0][1]);
}

bool cmp(int i, int j) {
    int x1 = max(x[idx[i][0]], max(x[idx[i][1]], x[idx[i][2]])), x2 = max(x[idx[j][0]], max(x[idx[j][1]], x[idx[j][2]]));
    return x1 < x2;
}

void intersect(int i, double x0, double x1) {
    int t[][2] = {{x[idx[i][0]], y[idx[i][0]]}, {x[idx[i][1]], y[idx[i][1]]}, {x[idx[i][2]], y[idx[i][2]]}};
    double y0[2], y1[2]; int c0 = 0, c1 = 0;
    for (int j=0; j<3; ++j) {
        int k = j<2 ? j+1 : 0;
        if (t[j][0] == t[k][0]) {
            if (abs(t[j][0]-x0) <= eps) y0[0] = t[j][1], y0[1] = t[k][1], c0 = 2;
            if (abs(t[j][0]-x1) <= eps) y1[0] = t[j][1], y1[1] = t[k][1], c1 = 2;
        } else {
            int a = min(t[j][0], t[k][0]), b = max(t[j][0], t[k][0]);
            if (c0 == 2 && abs(y0[0]-y0[1]) < eps) c0 = 1;
            if (c1 == 2 && abs(y1[0]-y1[1]) < eps) c1 = 1;
            if (c0 < 2 && x0 >= a-eps && x0 < b+eps)
                y0[c0++] = ((t[k][0] - x0) * t[j][1] + (x0 - t[j][0]) * t[k][1]) / (t[k][0] - t[j][0]);
            if (c1 < 2 && x1 >= a-eps && x1 < b+eps)
                y1[c1++] = ((t[k][0] - x1) * t[j][1] + (x1 - t[j][0]) * t[k][1]) / (t[k][0] - t[j][0]);
        }
    }
    s[v++] = {min(y0[0], y0[1]), min(y1[0], y1[1])}; s[v++] = {max(y0[0], y0[1]), max(y1[0], y1[1])};
}

double a2(double x1, double y1, double x2, double y2, double x3, double y3) {
    return abs((x2-x1)*(y3-y1) - (x3-x1)*(y2-y1));
}

bool point_int_tri(double xp, double yp, int i) {
    int x0 = x[idx[i][0]], y0 = y[idx[i][0]], x1 = x[idx[i][1]], y1 = y[idx[i][1]], x2 = x[idx[i][2]], y2 = y[idx[i][2]];
    double s = a2(x0, y0, x1, y1, x2, y2);
    return abs(a2(x0, y0, x1, y1, xp, yp) + a2(x0, y0, x2, y2, xp, yp) + a2(x1, y1, x2, y2, xp, yp) - s) < eps*s;
}

void solve() {
    for (int i=n=0; i<v; ++i) cin >> x[i] >> y[i] >> z[i], g[n++] = x[i];
    for (int i=m=0; i<t; ++i) calc_tri_params(idx[i], i);
    for (int i=0; i<m; ++i) for (int j=i+1; j<m; ++j) tri_intersect(e[i], e[j]);
    sort(e, e+m, cmp); sort(g, g+n); n = unique(g, g+n) - g;
    double ans = 0.;
    for (int i=1, j=0; i<n; ++i) {
        double x0 = g[i-1], x1 = g[i]; v = t = 0;
        if (x1-x0 < eps) continue;
        while (j < m && max(x[idx[e[j]][0]], max(x[idx[e[j]][1]], x[idx[e[j]][2]])) < x1-eps) ++j;
        for (int k=j; k<m; ++k) {
            if (min(x[idx[e[k]][0]], min(x[idx[e[k]][1]], x[idx[e[k]][2]])) > x0+eps) continue;
            q[t++] = e[k]; intersect(e[k], x0, x1);
        }
        sort(s, s+v);
        for (int k=1; k<v; ++k) {
            double y1 = s[k-1].y1, y2 = s[k-1].y2, y3 = s[k].y1, y4 = s[k].y2, xc, yc, zc; int c;
            if (abs(y3+y4-y1-y2) < eps) continue;
            abs(y3 - y1) < eps ? (xc = x0, yc = y1, c = 1) : (xc = x0+x0, yc = y1+y3, c = 2);
            abs(y4 - y2) < eps ? (xc += x1, yc += y2, c += 1) : (xc += x1+x1, yc += y2+y4, c += 2);
            xc = xc / c; yc = yc / c; c = -1; zc = -1e20;
            for (int p=0; p<t; ++p) if (point_int_tri(xc, yc, q[p])) {
                double z = (d[q[p]] - a[q[p]]*xc - b[q[p]]*yc) / ::c[q[p]];
                if (z > zc) c = q[p], zc = z;
            }
            if (c >= 0) ans += (x1-x0)*(y3+y4-y1-y2)*f[c];
        }
    }
    cout << "Case " << ++kase << ": " << ans / 2. << endl << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(2);
    while (cin >> v >> t && v) solve();
    return 0;
}