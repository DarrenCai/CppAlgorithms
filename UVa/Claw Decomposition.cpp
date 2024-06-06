/**
 * UVa11396
 * 爪分解
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 310
int g[N][3], c[N], color[N], n;

bool bipartite(int u) {
    for (int i=0, v; i<c[u]; ++i) {
        if (color[v = g[u][i]] == color[u]) return false;
        if (!color[v]) {
            color[v] = 3-color[u];
            if (!bipartite(v)) return false;
        }
    }
    return true;
}

void solve() {
    memset(c, 0, sizeof(c)); memset(color, 0, sizeof(color));
    int u, v, ok = 1;
    while (cin >> u >> v && u && v) g[u][c[u]++] = v, g[v][c[v]++] = u;
    for (int i=1; i<=n; ++i) if (!color[i]) {
        color[i] = 1;
        if (!bipartite(i)) {
            ok = 0; break;
        }
    }
    cout << (ok ? "YES" : "NO") << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) solve();
    return 0;
}