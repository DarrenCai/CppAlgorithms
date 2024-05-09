/**
 * UVa1494/LA5713
 * 秦始皇修路
 * Beijing 2011
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

#define N 1002
int g[N][N], c[N], x[N], y[N], p[N], f[N], m, n; double w[N][N], mx[N][N];
struct edge {
    int u, v; double w;
    bool operator< (const edge& rhs) const {
        return w < rhs.w;
    }
} e[N*N>>1]; 

int find(int x) {
    return x==f[x] ? x : f[x] = find(f[x]);
}

void dfs(int r, int u, int fa = -1, double x = 0.) {
    for (int i=0, v; i<c[u]; ++i) if ((v = g[u][i]) != fa) dfs(r, v, u, mx[r][v] = max(x, w[u][v]));
}

void solve() {
    cin >> n;
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i] >> p[i], f[i] = i, c[i] = 0;
    for (int i=m=0; i<n; ++i) for (int j=i+1; j<n; ++j) {
        e[m++] = {i, j, w[i][j] = w[j][i] = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]))};
        mx[i][j] = mx[j][i] = 0.;
    }
    sort(e, e+m);
    double cc = 0.;
    for (int i=0, t=0; i<m; ++i) {
        int u = e[i].u, v = e[i].v, x = find(u), y = find(v);
        if (x == y) continue;
        f[x] = y; cc += e[i].w; g[u][c[u]++] = v; g[v][c[v]++] = u;
        if (++t == n-1) break;
    }
    for (int i=0; i<n; ++i) dfs(i, i);
    double ans = 0.;
    for (int i=0; i<m; ++i) {
        int u = e[i].u, v = e[i].v;
        ans = max(ans, (p[u] + p[v]) / (cc - mx[u][v]));
    }
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(2);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}