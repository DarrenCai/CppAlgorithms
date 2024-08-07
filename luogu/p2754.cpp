/**
 * P2754 [CTSC1999] 家园 / 星际转移问题
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define M 20
#define N 15
#define T 128000
struct edge {int u, v, cap, flow;}; vector<edge> e;
int x[M][N], h[M], r[M], p[T], d[T], cur[T], num[T], m, n, k; bool f[N][N], vis[T]; vector<int> g[T];

void add_edge(int u, int v, int cap) {
    g[u].push_back(e.size()); e.push_back({u, v, cap, 0});
    g[v].push_back(e.size()); e.push_back({v, u, 0, 0});
}

bool bfs(int s, int t) {
    memset(vis, 0, sizeof(vis)); memset(d, 0, sizeof(d)); d[t] = 0; vis[t] = true;
    queue<int> q; q.push(t);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int i=g[v].size()-1; i>=0; --i) {
            const edge& ee = e[g[v][i]^1];
            if (!vis[ee.u] && ee.cap > ee.flow) vis[ee.u] = true, d[ee.u] = d[v] + 1, q.push(ee.u);
        }
    }
    return vis[s];
}

int solve() {
    memset(f, 0, sizeof(f));
    for (int i=0; i<m; ++i) {
        cin >> h[i] >> r[i];
        for (int j=0; j<r[i]; ++j) cin >> x[i][j];
        for (int j=0; j<r[i]; ++j) {
            int u = x[i][j], v = x[i][j==r[i]-1 ? 0 : j+1];
            if (u < 0) u = n+1;
            if (v < 0) v = n+1;
            f[u][v] = true;
        }
    }
    for (int k=1, x=n+1; k<=n; ++k) for (int i=0; i<=x; ++i) if (f[i][k])
        for (int j=0; j<=x; ++j) if (f[k][j]) f[i][j] = true;
    if (!f[0][n+1]) return 0;
    int s = 0, t = 2, flow = 0, cc = 0; e.clear();
    for (int i=n+2; i>=0; --i) g[i].clear();
    add_edge(1, t, k);
    while (flow < k) {
        for (int i=1, j=n*cc+n+3; i<=n; ++i, ++j) g[j].clear(), add_edge(j-n, j, k);
        for (int i=0; i<m; ++i) if (r[i] > 1) {
            int u = x[i][cc%r[i]], v = x[i][(cc+1)%r[i]];
            if (u < 0) continue;
            u = u ? n*cc+u+2 : 0; v = v < 0 ? 1 : (v ? n*cc+n+v+2 : 0);
            if (v == 0) continue;
            add_edge(u, v, h[i]);
        }
        ++cc;
        if (!bfs(s, t)) continue;
        int n1 = n*(cc+1) + 3, u = s;
        memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
        for (int i=0; i<n1; ++i) ++num[d[i]];
        while (d[s] < n1) {
            if (u == t) {
                int a = k;
                for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
                for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
                flow += a; u = s;
            }
            int ok = 0;
            for (int i=cur[u]; i<g[u].size(); ++i) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow && d[u] == d[ee.v] + 1) {
                    ok = 1; p[ee.v] = g[u][i]; cur[u] = i; u = ee.v;
                    break;
                }
            }
            if (!ok) {
                int m = n1 - 1;
                for (int i=g[u].size()-1; i>=0; --i) {
                    const edge& ee = e[g[u][i]];
                    if (ee.cap > ee.flow) m = min(m, d[ee.v]);
                }
                if (--num[d[u]] == 0) break;
                ++num[d[u] = m + 1]; cur[u] = 0;
                if (u != s) u = e[p[u]].u;
            }
        }
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m >> k) cout << solve() << endl;
    return 0;
}