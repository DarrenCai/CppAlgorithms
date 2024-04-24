/**
 * UVa1337/LA3192
 * 球的横切面
 * Ehime 2004
 */

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define eps 1e-4
#define M 20604
#define N 101
int f[M][N], b[M], x[N], y[N], z[N], r[N], m, n; double h[M]; bool k[N];

int find(int i, int x) {
    return x == f[i][x] ? x : f[i][x] = find(i, f[i][x]);
}

bool disj(int i, int j, double& zmin, double& zmax) {
    int dx = x[i]-x[j], dy = y[i]-y[j], dz = z[i]-z[j]; double d = sqrt(dx*dx+dy*dy+dz*dz);
    if (d >= r[i] + r[j]) return true;
    double c = (r[j]*r[j] + d*d - r[i]*r[i]) / 2. / r[j] / d, t = r[j]*sqrt(1-c*c);
    double f = r[j]*c/d, cz = z[j] + f*dz;
    zmin = cz - sqrt(dx*dx+dy*dy)/d*t; zmax = 2.*cz - zmin;
    if (dx*dx + dy*dy + (dz+r[i])*(dz+r[i]) <= r[j]*r[j]) zmax = z[i]+r[i];
    else if (dx*dx + dy*dy + (r[j]-dz)*(r[j]-dz) <= r[i]*r[i]) zmax = z[j]+r[j];
    if (dx*dx + dy*dy + (dz-r[i])*(dz-r[i]) <= r[j]*r[j]) zmin = z[i]-r[i];
    else if (dx*dx + dy*dy + (r[j]+dz)*(r[j]+dz) <= r[i]*r[i]) zmin = z[j]-r[j];
    return false;
}

void solve() {
    for (int i=m=0; i<n; ++i) cin >> x[i] >> y[i] >> z[i] >> r[i], k[i] = true, h[m++] = z[i]-r[i], h[m++] = z[i]+r[i];
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j)
        if (r[i]<r[j] && sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])+(z[i]-z[j])*(z[i]-z[j]))<=r[j]-r[i]) {
            k[i] = true; break;
        }
    for (int i=0; i<n; ++i) if (k[i]) for (int j=i+1; j<n; ++j) if (k[j]) {
        double zmin, zmax;
        if (disj(i, j, zmin, zmax)) continue;
        if (abs(zmin-z[i]+r[i])>eps && abs(zmin-z[j]+r[j])>eps) h[m++] = zmin;
        if (abs(zmax-z[i]-r[i])>eps && abs(zmax-z[j]-r[j])>eps) h[m++] = zmax;
    }
    sort(h, h+m); m = (unique(h, h+m) - h) << 1;
    for (int i=m-1; i>=0; --i) {
        h[i] = h[i>>1] + (i&1 ? eps : -eps);
        for (int j=0; j<n; ++j) f[i][j] = j;
    }
    for (int i=0; i<m; ++i) if (k[i]) for (int j=i+1; j<n; ++j) if (k[j]) {
        double zmin, zmax;
        if (disj(i, j, zmin, zmax)) continue;
        for (int p = upper_bound(h, h+m, zmin) - h; h[p] < zmax; ++p) f[p][find(p, j)] = find(p, i);
    }
    int t = 0;
    for (int i=0, c=0, d; i<m; ++i, c=d) {
        for (int j=d=0; j<n; ++j) if (k[j] && f[i][j] == j && h[i]>z[j]-r[j] && h[i]<z[j]+r[j]) ++d;
        if (d > c) b[t++] = 1;
        if (d < c) b[t++] = 0;
    }
    cout << t << endl;
    for (int i=0; i<t; ++i) cout << b[i];
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n && n) solve();
    return 0;
}