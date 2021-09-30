/**
 * UVa1279
 * 星际游击队
 */

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define N 55
int x[N], y[N], z[N], vx[N], vy[N], vz[N], adj[2][N], n, m, cc; double w[N];
struct node {
    int a, b, c, d; double t;
    bool operator< (const node& rhs) const {
        return t < rhs.t;
    }
} e[N*N*N*N];

void prim(double t) {
    bool add[N] = {false}; add[0] = true;
    int (&ref)[N] = adj[cc&1]; ref[0] = 0;
    for (int i=1; i<n; ++i) {
        double dx = (vx[0]-vx[i])*t + x[0]-x[i], dy = (vy[0]-vy[i])*t + y[0]-y[i], dz = (vz[0]-vz[i])*t + z[0]-z[i];
        w[i] = dx*dx + dy*dy + dz*dz;
        ref[i] = 0;
    }
    for (int i=1; i<n; ++i) {
        double m = __DBL_MAX__; int v = -1;
        for (int j=1; j<n; ++j) if (!add[j] && w[j]<m) m = w[j], v = j;
        add[v] = true;
        for (short j=1; j<n; ++j) if (!add[j]) {
            double dx = (vx[j]-vx[v])*t + x[j]-x[v], dy = (vy[j]-vy[v])*t + y[j]-y[v], dz = (vz[j]-vz[v])*t + z[j]-z[v];
            dx = dx*dx + dy*dy + dz*dz;
            if (dx < w[j]) w[j] = dx, ref[j] = v;
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int kase = 0;
    while (cin >> n) {
        for (int i=0; i<n; ++i) cin >> x[i] >> y[i] >> z[i] >> vx[i] >> vy[i] >> vz[i];
        m = cc = 0;
        for (int a=0; a<n; ++a) for (int b=a+1; b<n; ++b) for (int c=a; c<n; ++c) for (int d=(a==c ? b : c)+1; d<n; ++d) {
            double dx1 = x[a]-x[b], dy1 = y[a]-y[b], dz1 = z[a]-z[b],
                dx2 = x[c]-x[d], dy2 = y[c]-y[d], dz2 = z[c]-z[d],
                vx1 = vx[a]-vx[b], vy1 = vy[a]-vy[b], vz1 = vz[a]-vz[b],
                vx2 = vx[c]-vx[d], vy2 = vy[c]-vy[d], vz2 = vz[c]-vz[d];
            double A = vx1*vx1 + vy1*vy1 + vz1*vz1 - vx2*vx2 - vy2*vy2 - vz2*vz2,
                B = 2*(vx1*dx1 + vy1*dy1 + vz1*dz1 - vx2*dx2 - vy2*dy2 - vz2*dz2),
                C = dx1*dx1 + dy1*dy1 + dz1*dz1 - dx2*dx2 - dy2*dy2 - dz2*dz2,
                D = B*B - 4*A*C;
            if (A != 0.) {
                if (D > 0.) {
                    D = sqrt(D); A = 2*A;
                    double t = (D-B)/A;
                    if (t > 0.) e[m].a = a, e[m].b = b, e[m].c = c, e[m].d = d, e[m++].t = t+5e-7;
                    t = (-D-B)/A;
                    if (t > 0.) e[m].a = a, e[m].b = b, e[m].c = c, e[m].d = d, e[m++].t = t+5e-7;
                }
            } else if (B != 0.) {
                double t = -C/B;
                if (t > 0.) e[m].a = a, e[m].b = b, e[m].c = c, e[m].d = d, e[m++].t = t+5e-7;
            }
        }
        if (m > 0) sort(e, e+m);
        prim(0.); ++cc;
        for (int i=0; i<m; ++i) {
            int a = e[i].a, b = e[i].b, c = e[i].c, d = e[i].d, (&pre)[N] = adj[~cc&1], (&cur)[N] = adj[cc&1]; double t = e[i].t;
            if ((pre[a]==b || pre[b]==a) && pre[c]!=d && pre[d]!=c) {
                double dx = (vx[a]-vx[b])*t + x[a]-x[b], dy = (vy[a]-vy[b])*t + y[a]-y[b], dz = (vz[a]-vz[b])*t + z[a]-z[b];
                double w1 = dx*dx + dy*dy + dz*dz;
                dx = (vx[c]-vx[d])*t + x[c]-x[d], dy = (vy[c]-vy[d])*t + y[c]-y[d], dz = (vz[c]-vz[d])*t + z[c]-z[d];
                if (w1 > dx*dx + dy*dy + dz*dz) {
                    prim(t);
                    if (cur[c]==d || cur[d]==c) ++cc;
                }
            } else if ((pre[c]==d || pre[d]==c) && pre[a]!=b && pre[b]!=a) {
                double dx = (vx[a]-vx[b])*t + x[a]-x[b], dy = (vy[a]-vy[b])*t + y[a]-y[b], dz = (vz[a]-vz[b])*t + z[a]-z[b];
                double w1 = dx*dx + dy*dy + dz*dz;
                dx = (vx[c]-vx[d])*t + x[c]-x[d], dy = (vy[c]-vy[d])*t + y[c]-y[d], dz = (vz[c]-vz[d])*t + z[c]-z[d];
                if (w1 < dx*dx + dy*dy + dz*dz) {
                    prim(t);
                    if (cur[a]==b || cur[b]==a) ++cc;
                }
            }
        }
        cout << "Case " << ++kase << ": " << cc << endl;
    }
    return 0;
}