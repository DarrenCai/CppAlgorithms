/**
 * UVa1086/LA4452
 * 投票
 * World Finals >> 2009 - Stockholm
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 206
int g[N][N], c[N], s[N], x[N], v[4], p, m, n, t, kase = 0; bool vis[N][N], f[N];

bool check(int u, int r) {
    s[p++] = u; x[u] = r;
    while (p) {
        u = s[--p];
        for (int i=0, v; i<c[u]; ++i) if (x[v = g[u][i]] != r) {
            if (!f[v] || x[v^1] == r) return false;
            s[p++] = v; x[v] = r;
        }
    }
    return true;
}

void solve() {
    t = (m+1)<<1; memset(c, 0, sizeof(c)); memset(f, 1, sizeof(f));
    memset(vis, 0, sizeof(vis)); memset(x, 0, sizeof(x));
    for (int i=0; i<n; ++i) {
        int cc; cin >> cc;
        for (int j=0; j<cc; ++j) {
            int x; char ch; cin >> x >> ch; v[j] = x<<1 | ch=='n';
        }
        if (cc > 2) {
            for (int j=0; j<cc; ++j) for (int k=0, x=v[j]^1, y; k<cc; ++k) if (j!=k && !vis[x][y=v[k]])
                g[x][c[x]++] = y, vis[x][y] = true;
        } else for (int j=0; j<cc; ++j) f[v[j]^1] = false;
    }
    cout << "Case " << ++kase << ": ";
    for (int u=2; u<t; ++u) {
        if (f[u]) p = 0, f[u] = check(u, u);
        if (!f[u] && !f[u^1]) {
            cout << "impossible" << endl; return;
        }
    }
    for (int i=2; i<t; i+=2) cout << (f[i] && f[i^1] ? '?' : (f[i] ? 'y' : 'n'));
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> m >> n && m) solve();
    return 0;
}