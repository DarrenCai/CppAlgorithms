/**
 * UVa1359/LA3491
 * 数小山
 * Hangzhou 2005
 */

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define N 504
int x[N], y[N], vx[N], vy[N], c[2][N], n; double l[N];
struct frac {
    int p, q;
    bool operator== (const frac& rhs) const {
        return p*(long long)rhs.q - q*(long long)rhs.p == 0;
    }
};

struct je {
    frac f, e; double t; int i;
    bool operator< (const frac& r) const {
        return f.p*(long long)r.q - f.q*(long long)r.p < 0;
    }
    bool operator< (const je& rhs) const {
        return f.p*(long long)rhs.f.q - f.q*(long long)rhs.f.p < 0;
    }
} a[2][N][N];

void merge(je (&a)[N], int &c) {
    sort(a, a+c);
    int k = 0;
    for (int j=1; j<c; ++j) {
        if (a[k] < a[j]) a[++k] = a[j];
        else if (a[j].t < a[k].t) a[k].e = a[j].e, a[k].t = a[j].t, a[k].i = a[j].i;
    }
    c = ++k;
}

int solve() {
    cin >> n;
    for (int i=0; i<n; ++i) {
        cin >> x[i] >> y[i] >> vx[i] >> vy[i];
        c[0][i] = c[1][i] = 0; vx[i] -= x[i]; vy[i] -= y[i];
        l[i] = sqrt(vx[i]*vx[i] + vy[i]*vy[i]);
    }
    for (int i=0; i<n; ++i) {
        for (int j=i+1; j<n; ++j) {
            int ux = x[i] - x[j], uy = y[i] - y[j];
            int p1 = vx[j]*uy - ux*vy[j], p2 = vx[i]*uy - ux*vy[i], q0 = vx[i]*vy[j] - vx[j]*vy[i], q = q0;
            if (q < 0) p1 = -p1, p2 = -p2, q = -q;
            if (p1 < 0 || p1 > q || p2 < 0 || p2 > q) continue;
            double t = (vx[i]*vx[j] + vy[i]*vy[j]) / l[i] / l[j];
            je &ef = a[0][i][c[0][i]++], &eb = a[1][i][c[1][i]++], &ff = a[0][j][c[0][j]++], &fb = a[1][j][c[1][j]++];
            ef.f.q = eb.f.q = ff.f.q = fb.f.q = q; ef.f.p = p1; eb.f.p = q-p1; ff.f.p = p2; fb.f.p = q-p2;
            if (q0 > 0) {
                ef.e = ff.f; eb.e = fb.f; ef.t = eb.t = t; ef.i = j; eb.i = j+n;
                ff.e = eb.f; fb.e = ef.f; ff.t = fb.t = -t; ff.i = i+n; fb.i = i;
            } else {
                ef.e = fb.f; eb.e = ff.f; ef.t = eb.t = -t; ef.i = j+n; eb.i = j;
                ff.e = ef.f; fb.e = eb.f; ff.t = fb.t = t; ff.i = i; fb.i = i+n;
            }
        }
        merge(a[0][i], c[0][i]); merge(a[1][i], c[1][i]);
    }
    int s = 0;
    for (int i=0; i<n; ++i) for (int j=0; j<2; ++j) for (int k=1; k<c[j][i]; ++k) {
        je &e = a[j][i][k]; int r = e.i < n ? 0 : 1, m = e.i < n ? e.i : e.i-n, t = c[r][m];
        je (&p)[N] = a[r][m]; int x = lower_bound(p, p+t, e.e) - p + 1;
        if (x == t) continue;
        je &b = p[x]; r = b.i < n ? 0 : 1; m = b.i < n ? b.i : b.i-n; t = c[r][m];
        je (&u)[N] = a[r][m]; x = lower_bound(u, u+t, b.e) - u + 1;
        if (x < t && u[x].i == j*n+i && u[x].e == a[j][i][k-1].f) ++s;
    }
    return s / 3;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) {
        cout << "Case " << kase << ':' << endl << solve() << endl;
        if (kase < t) cout << endl;
    }
    return 0;
}
