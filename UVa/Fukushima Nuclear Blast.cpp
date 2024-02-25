/**
 * UVa11978
 * 福岛核泄漏
 */

#include <iostream>
#include <cmath>
using namespace std;

#define eps 1e-2
#define N 5005
int x[N], y[N], a[N], n, cx, cy, p; double vx[N], vy[N], d2[N], e[N], f[N], g[N], z[N];

double area2(double r) {
    double s = 0., r2 = r*r;
    for (int i=0; i<n; ++i) {
        if (a[i] == 0) continue;
        int j = i+1<n ? i+1 : 0;
        if (d2[i] < r2) {
            if (f[i] > r) {
                double d = sqrt(r2 - d2[i]), b = e[i] - d, c = e[i] + d;
                if (c < 0. || b >= z[i]) {
                    s += g[i] * r2; continue;
                }
                double x1 = x[i] + vx[i]*b, y1 = y[i] + vy[i]*b, t = acos((f[i]*f[i] + r2 - b*b)/2./f[i]/r);
                if (f[j] > r) {
                    double x2 = x[i] + vx[i]*c, y2 = y[i] + vy[i]*c; t = abs(g[i]) - 2*asin(d/r);
                    s += (a[i]<0 ? -t : t) * r2 + (x1-cx) * (y2-cy) - (x2-cx) * (y1-cy);
                } else s += (a[i]<0 ? -t : t) * r2 + (x1-cx) * (y[j]-cy) - (x[j]-cx) * (y1-cy);
            } else if (f[j] > r) {
                double b = e[i] + sqrt(r2 - d2[i]), x1 = x[i] + vx[i]*b, y1 = y[i] + vy[i]*b;
                double t = acos((f[j]*f[j] + r2 - (z[i]-b)*(z[i]-b))/2./f[j]/r);
                s += (a[i]<0 ? -t : t) * r2 + (x[i]-cx) * (y1-cy) - (x1-cx) * (y[i]-cy);
            } else s += a[i];
        } else s += g[i] * r2;
    }
    return s;
}

int solve() {
    cin >> n;
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i];
    double l = 0., r = 0., s = 0.;
    cin >> cx >> cy >> p;
    for (int i=0; i<n; ++i) {
        int j = i+1<n ? i+1 : 0, dx = cx - x[i], dy = cy - y[i];
        f[i] = sqrt(dx*dx + dy*dy); r = max(f[i], r);
        if ((a[i] = dx*(cy-y[j]) - (cx-x[j])*dy) == 0) continue;
        vx[i] = x[j] - x[i]; vy[i] = y[j] - y[i]; z[i] = sqrt(vx[i]*vx[i] + vy[i]*vy[i]); vx[i] /= z[i];
        vy[i] /= z[i]; d2[i] = abs(a[i] / z[i]); d2[i] *= d2[i]; e[i] = dx*vx[i] + dy*vy[i]; s += a[i];
    }
    for (int i=0, j; i<n; ++i) {
        if (a[i] == 0) continue;
        g[i] = acos(((cx - x[i]) * (cx - x[j = i+1<n ? i+1 : 0]) + (cy - y[i]) * (cy - y[j])) / f[i] / f[j]);
        if (a[i] < 0) g[i] = -g[i];
    }
    if (p == 100) return r + .5;
    s *= p / 100.;
    while (l + eps < r) {
        double m = (l + r) / 2;
        area2(m) > s ? r = m-eps : l = m;
    }
    return r + .5;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Case " << kase << ": " << solve() << endl;
    return 0;
}
