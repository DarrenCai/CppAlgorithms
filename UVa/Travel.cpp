/**
 * UVa1369/LA3604
 * Seoul 2006
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 500000
#define N 2002
struct edge {int u, v, cap, flow, cost;} e[N*N>>1];
int g[N][N>>1], q[N], p[N], d[N], cur[N], num[N+1], cnt[N], u[M], v[M], id[N>>1][N>>1], c, m, n; bool f[M], vis[N];

void add_edge(int u, int v, int cap) {
    e[c] = {u, v, cap, 0}; g[u][cnt[u]++] = c++; e[c] = {v, u, 0, 0}; g[v][cnt[v]++] = c++;
}

bool bfs(int s, int t) {
    memset(vis, 0, sizeof(vis)); q[0] = t; d[t] = 0; vis[t] = true;
    int head = 0, tail = 1;
    while (head < tail) {
        int v = q[head++];
        for (int i=0; i<cnt[v]; ++i) {
            const edge& ee = e[g[v][i]^1];
            if (!vis[ee.u] && ee.cap > ee.flow) vis[ee.u] = true, d[ee.u] = d[v] + 1, q[tail++] = ee.u;
        }
    }
    return vis[s];
}

bool solve() {
    cin >> n >> m; memset(cnt, c = 0, sizeof(cnt));
    for (int i=0; i<m; ++i) cin >> u[i] >> v[i], f[i] = true, id[u[i]][v[i]] = id[v[i]][u[i]] = i;
    int s = 0, t = 2*n+1, flow = 0, x, y, z, w; cin >> x >> y >> z >> w; f[id[x][y]] = f[id[z][w]] = false;
    add_edge(s, x, 1); add_edge(s, y, 1); add_edge(z+n, t, 1); add_edge(w+n, t, 1); cin >> x;
    while (x--) cin >> y >> z, f[id[y][z]] = false;
    for (int i=1; i<=n; ++i) add_edge(i, i+n, 1);
    for (int i=0; i<m; ++i) if (f[i]) add_edge(u[i]+n, v[i], 1), add_edge(v[i]+n, u[i], 1);
    for (int i=0; i<=t; ++i) d[i] = t+1;
    if (!bfs(s, t)) return false;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    for (int u=s; d[s] <= t;) {
        if (u == t) {
            int a = 1;
            for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
            for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
            flow += a; u = s;
        }
        bool ok = false;
        for (int i=cur[u]; i<cnt[u]; ++i) {
            const edge& ee = e[g[u][i]];
            if (ee.cap > ee.flow && d[u] == d[ee.v] + 1) {
                ok = true; p[ee.v] = g[u][i]; cur[u] = i; u = ee.v;
                break;
            }
        }
        if (!ok) {
            int m = t;
            for (int i=0; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow) m = min(m, d[ee.v]);
            }
            if (--num[d[u]] == 0) break;
            ++num[d[u] = m + 1]; cur[u] = 0;
            if (u != s) u = e[p[u]].u;
        }
    }
    return flow == 2;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) cout << (solve() ? "YES" : "NO") << endl;
    return 0;
}