/**
 * UVa1060/LA2397
 * 拿行李
 * World Finals >> 2007 - Tokyo
 */

#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

#define INF 1e20
#define eps 1e-8
#define N 102
int x[N], y[N], c[N], px, py, vl, vp, n, kase = 0; double d[N], s[N], w[N], mx; bool f[N];
struct {int v; double w;} g[N][N];
struct node {
    double d; int u;
    bool operator< (const node& rhs) const {
        return d>rhs.d;
    }
};

int dcmp(double x) {
    return abs(x) < eps ? 0 : (x < 0. ? -1 : 1);
}

bool point_in_poly(double xp, double yp) {
    int wn = 0;
    for (int i=0; i<n; ++i) {
        int j = i+1 < n ? i+1 : 0, dx = x[j]-x[i], dy = y[j]-y[i];
        double vx = xp-x[i], vy = yp-y[i], c = dx*vy - dy*vx, d = (vx*dx + vy*dy) / (dx*dx + dy*dy);
        if (abs(c) < eps && d > -eps && d < 1+eps) return false;
        int k = dcmp(c), d1 = dcmp(y[i]-yp), d2 = dcmp(y[j]-yp);
        if (k > 0 && d1 <= 0 && d2 > 0) ++wn;
        if (k < 0 && d2 <= 0 && d1 > 0) --wn;
    }
    return wn != 0;
}

bool seg_visible(double xa, double ya, double xb, double yb) {
    double vx = xb-xa, vy = yb-ya;
    for (int i=0; i<n; ++i) {
        int j = i+1 < n ? i+1 : 0, dx = x[j]-x[i], dy = y[j]-y[i];
        double ex = x[i]-xa, ey = y[i]-ya, c = vx*dy - vy*dx;
        if (abs(c) < eps) continue;
        double d = (ex*dy - ey*dx) / c, e = (ex*vy - ey*vx) / c;
        if (e > -eps && e < 1+eps && d > eps && d < 1-eps) return false;
    }
    return !point_in_poly(.5*(xa+xb), .5*(ya+yb));
}

int to_sec(double x) {
    return 60*x + .5;
}

void solve() {
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i], c[i] = f[i] = 0, d[i] = INF;
    cin >> px >> py >> vl >> vp; s[0] = 0.; mx = INF;
    priority_queue<node> q;
    for (int i=0; i<n; ++i) {
        int j = i+1 < n ? i+1 : 0, il = i ? i-1 : n-1, ir = j;
        if (seg_visible(x[i], y[i], px, py)) q.push({d[i] = sqrt((x[i]-px)*(x[i]-px) + (y[i]-py)*(y[i]-py)), i});
        w[i] = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j])); s[i+1] = s[i] + w[i];
        g[i][c[i]++] = {j, w[i]}; g[j][c[j]++] = {i, w[i]};
        for (j=0; j<n; ++j) if (j!=i && j!=il && j!=ir && seg_visible(x[i], y[i], x[j], y[j])) {
            double w = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
            g[i][c[i]++] = {j, w}; g[j][c[j]++] = {i, w};
        }
    }
    while (!q.empty()) {
        int u = q.top().u; q.pop();
        if (d[u] < mx) mx = d[u];
        if (f[u]) continue;
        f[u] = true;
        for (int i=0; i<c[u]; ++i) {
            int v = g[u][i].v; double d1 = d[u] + g[u][i].w;
            if (d[v] > d1) q.push({d[v] = d1, v});
        }
    }
    double l = 0., r = mx / vp + s[n] / (vl+vp);
    while (to_sec(l) < to_sec(r)) {
        double m = (l+r) / 2., t = m*vl; int e = t / s[n], k = upper_bound(s, s+n, t-e*s[n]) - s - 1;
        double t1 = t - e*s[n] - s[k]; bool ok = false;
        if (t1 < eps) ok = d[k] < m*vp;
        else if (t1 > w[k]-eps) ok = d[k+1 < n ? k+1 : 0] < m*vp;
        else {
            t1 /= w[k];
            int i = k+1 < n ? k+1 : 0; double xc = x[k]*(1-t1) + x[i]*t1, yc = y[k]*(1-t1) + y[i]*t1;
            if (seg_visible(xc, yc, px, py)) ok = sqrt((xc-px)*(xc-px) + (yc-py)*(yc-py)) < m*vp;
            else {
                t1 = INF;
                for (i=0; i<n; ++i) if (seg_visible(xc, yc, x[i], y[i]))
                    t1 = min(t1, d[i] + sqrt((xc-x[i])*(xc-x[i]) + (yc-y[i])*(yc-y[i])));
                ok = t1 < m*vp;
            }
        }
        ok ? r = m-eps : l = m+eps;
    }
    int v = to_sec(r);
    cout << "Case " << ++kase << ": Time = " << v/60 << ':';
    if ((v %= 60) < 10) cout << '0';
    cout << v << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) solve();
    return 0;
}