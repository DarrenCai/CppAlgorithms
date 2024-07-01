/**
 * UVa11367
 * 加满油
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define INF 20000000
#define C 102
#define N 1001
struct node {
    int u, c, d;
    bool operator< (const node& rhs) const {
        return d > rhs.d;
    }
};
int d[N][C], g[N][10*N], w[N][10*N], c[N], p[N], m, n; bool f[N][C];

void query() {
    int v, s, e; cin >> v >> s >> e;
    memset(d, 2, sizeof(d)); memset(f, 0, sizeof(f)); d[s][0] = 0;
    priority_queue<node> q; q.push({s, 0, 0});
    while (!q.empty()) {
        node t = q.top(); q.pop(); int u = t.u, x = t.c, r = d[u][x];
        if (u == e && x == 0) break;
        if (f[u][x]) continue;
        f[u][x] = true;
        for (int i=0, y, z; i<c[u]; ++i) if (x >= (z = w[u][i]) && r < d[y=g[u][i]][x-z])
            q.push({y, z=x-z, d[y][z] = r});
        if (++x <= v && r + p[u] < d[u][x]) q.push({u, x, d[u][x] = r + p[u]});
    }
    d[e][0] < INF ? cout << d[e][0] << endl : cout << "impossible" << endl;
}

void solve() {
    for (int i=0; i<n; ++i) cin >> p[i], c[i] = 0;
    while (m--) {
        int u, v, d; cin >> u >> v >> d;
        g[u][c[u]] = v; g[v][c[v]] = u; w[u][c[u]++] = w[v][c[v]++] = d;
    }
    int q; cin >> q;
    while (q--) query();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) solve();
    return 0;
}