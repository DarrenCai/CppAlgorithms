/**
 * P3171 [CQOI2015] 网络吞吐量
 */

#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

#define INF 0x7f7f7f7f
#define M 100502
#define N 502
#define T 1002
struct {int u, v, w;} e0[M]; struct edge {int u, v, cap, flow;} e[M<<1];
vector<int> g[T]; int q[T], p[T], cur[T], num[T], c, m, n; long long d[T]; bool vis[T];
struct node {
    int u; long long d;
    bool operator< (const node& rhs) const {
        return d > rhs.d;
    }
};

void add_edge(int u, int v, int cap, int cc = 0) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u].push_back(c++);
    e[c].u = v; e[c].v = u; e[c].cap = cc; e[c].flow = 0; g[v].push_back(c++);
}

bool bfs(int s, int t) {
    memset(vis, 0, sizeof(vis)); memset(d, 0, sizeof(d)); q[0] = t; d[t] = 0; vis[t] = true;
    int head = 0, tail = 1;
    while (head < tail) {
        int v = q[head++];
        for (int i=g[v].size()-1; i>=0; --i) {
            const edge& ee = e[g[v][i]^1];
            if (!vis[ee.u] && ee.cap > ee.flow) vis[ee.u] = true, d[ee.u] = d[v] + 1, q[tail++] = ee.u;
        }
    }
    return vis[s];
}

long long solve() {
    memset(d, 0x7f, sizeof(d)); memset(vis, c = 0, sizeof(vis));
    for (int i=1; i<T; ++i) g[i].clear();
    for (int i=0; i<m; ++i) {
        int u, v, w; cin >> u >> v >> w; e0[i] = {u, v, w}; g[u].push_back(i); g[v].push_back(i);
    }
    queue<int> q; d[1] = 0; q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop(); vis[u] = false;
        for (int i=g[u].size()-1; i>=0; --i) {
            int j = g[u][i], v = e0[j].u + e0[j].v - u; long long d1 = d[u] + e0[j].w;
            if (d[v] > d1) {
                d[v] = d1;
                if (!vis[v]) q.push(v), vis[v] = true;
            }
        }
    }
    for (int i=1; i<=n; ++i) g[i].clear();
    for (int i=1; i<=n; ++i) {
        int w; cin >> w;
        if (i>1 && i<n) add_edge(i, i+n-1, w);
    }
    int s = 1, t = n, u = s; long long cc = 0;
    for (int i=0; i<m; ++i) {
        int u = e0[i].u, v = e0[i].v, w = e0[i].w;
        if (d[u] + w == d[v]) {
            add_edge(u>s ? u+n-1 : s, v, INF, d[v] + w == d[u] ? INF : 0);
        } else if (d[v] + w == d[u]) add_edge(v>s ? v+n-1 : s, u, INF);
    }
    n += n-1;
    if (!bfs(s, t)) return cc;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=1; i<=n; ++i) if (d[i] < INF) ++num[d[i]];
    while (d[s] < n) {
        if (u == t) {
            int a = INF;
            for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
            for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
            cc += a; u = s;
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
            int m = n - 1;
            for (int i=0; i<g[u].size(); ++i) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow) m = min(m, int(d[ee.v]));
            }
            if (--num[d[u]] == 0) break;
            ++num[d[u] = m + 1]; cur[u] = 0;
            if (u != s) u = e[p[u]].u;
        }
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) cout << solve() << endl;
    return 0;
}