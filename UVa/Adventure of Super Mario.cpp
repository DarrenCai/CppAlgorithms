/**
 * UVa10269
 * 超级马里奥大冒险
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define K 11
#define N 102
#define L 505
struct node {int p, k, l;};
int d[N][K][L], g[N][N], w[N][N], c[N], a, b, m, l, k; bool f[N][K][L];

void solve() {
    int ans = 10000000;
    memset(c, 0, sizeof(c)); memset(d, 1, sizeof(d)); memset(f, 0, sizeof(f));
    cin >> a >> b >> m >> l >> k;
    while (m--) {
        int u, v, l; cin >> u >> v >> l; g[u][c[u]] = v; g[v][c[v]] = u; w[u][c[u]++] = w[v][c[v]++] = l;
    }
    queue<node> q; d[b += a][k][0] = 0; q.push({b, k, 0});
    while (!q.empty()) {
        node t = q.front(); q.pop(); int u = t.p, e = t.k, h = t.l, r = d[u][e][h]; f[u][e][h] = false;
        for (int i=0; i<c[u]; ++i) {
            int v = g[u][i], x = w[u][i], y;
            if (r + x < d[v][e][0]) {
                d[v][e][0] = r + x;
                if (!f[v][e][0]) q.push({v, e, 0}), f[v][e][0] = true;
                if (v == 1) ans = min(ans, d[v][e][0]);
            }
            if (h >= x && r < d[v][e][y = v > a ? 0 : h-x]) {
                d[v][e][y] = r;
                if (!f[v][e][y]) q.push({v, e, y}), f[v][e][y] = true;
                if (v == 1) ans = min(ans, r);
            }
            if (e && l >= x && r < d[v][e-1][y = v > a ? 0 : l-x]) {
                d[v][e-1][y] = r;
                if (!f[v][e-1][y]) q.push({v, e-1, y}), f[v][e-1][y] = true;
                if (v == 1) ans = min(ans, r);
            }
        }
    }
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}