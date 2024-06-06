/**
 * UVa1310/LA2664
 * CERC 2002
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 2020000
#define N 2020
int g[N][N], c[N], x[M], y[M], d[M], f[M], pre[N], s[M], bn[N], bcc[N], iu[N], clk, cc, m, n, p; bool vis[M];

void det(int t) {
    for (int i=0; i<t; ++i) {
        int u = bcc[i], n = 0, s = -1; iu[u] = 0;
        for (int j=0; j<c[u]; ++j) {
            int e = g[u][j], v = x[e] + y[e] - u;
            if (bn[v] != cc) continue;
            !f[e] && d[e]==2 ? (++n, s = e) : iu[u] |= f[e] ? f[e] : u==x[e] ? 1 : 2;
        }
        int k = iu[u]^3;
        if (k && n == 1) {
            int v = x[s] + y[s] - u; iu[u] = 3;
            if (k == 3) {
                f[s] = 3;
            } else if (k == 1) {
                f[s] = u == x[s] ? 1 : 2;
            } else {
                f[s] = u == y[s] ? 1 : 2;
            }
        }
    }
    for (int i=0, u; i<t; ++i) if (iu[u = bcc[i]] < 3) for (int j=0; j<c[u]; ++j) {
        int e = g[u][j], v = x[e] + y[e] - u;
        if (bn[v] != cc || f[e] || d[e] == 1) continue;
        if (iu[u] == 1) {
            f[e] = u == y[e] ? 1 : 2; iu[v] |= 1; iu[u] = 3;
        } else {
            f[e] = u == x[e] ? 1 : 2; iu[v] |= 2; iu[u] |= 1;
        }
        if (iu[u] == 3) break;
    }
}
    
int dfs(int u, int fa = -1) {
    int low = pre[u] = ++clk;
    for (int i=0; i<c[u]; ++i) {
        int e = g[u][i], v = x[e] + y[e] - u;
        if (vis[e]) continue;
        vis[e] = true; s[p++] = e;
        if (!pre[v]) {
            int lowv = dfs(v, u); low = min(low, lowv);
            if (lowv >= pre[u]) {
                ++cc; int t = 0;
                while (true) {
                    int j = s[--p], a = x[j], b = y[j];
                    if (bn[a] != cc) bn[a] = cc, bcc[t++] = a;
                    if (bn[b] != cc) bn[b] = cc, bcc[t++] = b;
                    if (j == e) break;
                }
                det(t);
            }
        } else if (pre[v] < pre[u] && v != fa) low = min(low, pre[v]);
    }
    return low;
}

void solve() {
    memset(c, 0, sizeof(c)); memset(f, 0, sizeof(f));
    memset(pre, clk = 0, sizeof(pre)); memset(bn, cc = p = 0, sizeof(bn));
    for (int i=0; i<m; ++i) {
        cin >> x[i] >> y[i] >> d[i];
        g[x[i]][c[x[i]]++] = g[y[i]][c[y[i]]++] = i; vis[i] = false;
    }
    for (int u=1; u<=n; ++u) if (!pre[u]) dfs(u);
    for (int i=0; i<m; ++i) if (d[i] == 2) {
        if (f[i] == 3) {
            cout << x[i] << ' ' << y[i] << ' ' << 2 << endl;
        } else if (f[i] == 2) {
            cout << y[i] << ' ' << x[i] << ' ' << 1 << endl;
        } else cout << x[i] << ' ' << y[i] << ' ' << 1 << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) solve();
    return 0;
}