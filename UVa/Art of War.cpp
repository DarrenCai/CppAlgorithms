/**
 * UVa1334/LA3176
 * 战争的艺术
 * CERC 2004
 */

#include <iostream>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;

#define M 4002
#define N 602
int p[N][M], g[M][M], c[M], e[N], f[N], x[M], y[M], a[N], b[N], m, n, t; double l[M][M]; bool vis[M][M];

void check() {
    double s = 0.;
    for (int i=0; i<e[m]; ++i) {
        int u = p[m][i], v = p[m][i+1];
        s += x[u]*y[v] - x[v]*y[u];
    }
    if (s > 0.) ++m;
}

void dfs(int u, int i, int s) {
    vis[u][i] = true;
    if (u == s) p[m][0] = s, e[m] = 1;
    int v = g[u][i]; double a = x[v] - x[u], b = y[v] - y[u];
    if (v != s) {
        p[m][e[m]++] = v; int z = -1; double t = 4.;
        for (int j=0, w; j<c[v]; ++j) if (!vis[v][j] && (w = g[v][j]) != u) {
            double c = x[w] - x[v], d = y[w] - y[v], f = (a*c + b*d) / l[u][i] / l[v][j];
            if (a*d - c*b < 0.) f = 2. - f;
            if (f < t) z = j, t = f;
        }
        if (z >= 0) dfs(v, z, s);
    } else p[m][e[m]] = s, check();
}

void find(int u) {
    for (int i=0, wn; i<m; ++i) {
        for (int j=wn=0; j<e[i]; ++j) {
            int v = p[i][j], w = p[i][j+1];
            double k = (x[w] - x[v]) * (b[u] - y[v]) - (a[u] - x[v]) * (y[w] - y[v]);
            if (k > 0. && y[v] <= b[u] && y[w] > b[u]) ++wn;
            if (k < 0. && y[w] <= b[u] && y[v] > b[u]) --wn;
        }
        if (wn) {
            f[i] = u; return;
        }
    }
}

void solve() {
    for (int i=1; i<=n; ++i) cin >> a[i] >> b[i];
    map<pair<int, int>, int> id;
    for (int i=t=0; i<m; ++i) {
        cin >> x[t] >> y[t]; pair<int, int> a(x[t], y[t]);
        int u = id.count(a) ? id[a] : (c[t] = 0, id[a] = t++);
        cin >> x[t] >> y[t]; a = pair<int, int>(x[t], y[t]);
        int v = id.count(a) ? id[a] : (c[t] = 0, id[a] = t++);
        g[u][c[u]] = v; g[v][c[v]] = u; vis[u][c[u]] = vis[v][c[v]] = false;
        l[u][c[u]++] = l[v][c[v]++] = sqrt((x[u]-x[v])*(x[u]-x[v]) + (y[u]-y[v])*(y[u]-y[v]));
    }
    for (int i=m=0; i<t; ++i) for (int j=0; j<c[i]; ++j) if (!vis[i][j]) dfs(i, j, i);
    for (int i=1; i<=n; ++i) c[i] = 0, find(i);
    map<pair<int, int>, int> mp;
    for (int i=0; i<m; ++i) for (int j=0; j<e[i]; ++j) mp[pair<int, int>(p[i][j], p[i][j+1])] = f[i];
    for (int i=0; i<m; ++i) {
        int r = f[i];
        for (int j=0; j<e[i]; ++j) {
            pair<int, int> a(p[i][j+1], p[i][j]);
            if (mp.count(a)) g[r][c[r]++] = mp[a];
        }
        sort(g[r], g[r]+c[r]); c[r] = unique(g[r], g[r]+c[r]) - g[r];
    }
    for (int i=1; i<=n; ++i) {
        cout << c[i];
        for (int j=0; j<c[i]; ++j) cout << ' ' << g[i][j];
        cout << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m && (m || n)) solve();
    return 0;
}