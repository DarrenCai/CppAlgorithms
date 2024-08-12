/**
 * LibreOJ-117
 * 有源汇有上下界最小流
 * https://vjudge.net/problem/LibreOJ-117
 */

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define INF 0x7f7f7f7f
#define M 750024
#define N 50006
struct edge {int u, v, cap, flow;} e[M]; vector<int> g[N];
int q[N], p[N], d[N], cur[N], num[N], cs[N], ct[N], c, m, n, f; bool vis[N];

void add_edge(int u, int v, int cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u].push_back(c++);
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v].push_back(c++);
}

bool bfs(int s, int t) {
    memset(vis, 0, sizeof(vis)); memset(d, 0, sizeof(d)); q[0] = t; d[t] = 0; vis[t] = true;
    int head = 0, tail = 1;
    while (head < tail) {
        int v = q[head++];
        for (int i=0; i<g[v].size(); ++i) {
            const edge& ee = e[g[v][i]^1];
            if (!vis[ee.u] && ee.cap > ee.flow) vis[ee.u] = true, d[ee.u] = d[v] + 1, q[tail++] = ee.u;
        }
    }
    return vis[s];
}

int max_flow(int s, int t, int n) {
    int flow = 0, u = s;
    if (!bfs(s, t)) return 0;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<n; ++i) ++num[d[i]];
    while (d[s] < n) {
        if (u == t) {
            int a = INF;
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
            int m = n-1;
            for (int i=0; i<g[u].size(); ++i) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow) m = min(m, d[ee.v]);
            }
            if (--num[d[u]] == 0) break;
            ++num[d[u] = m + 1]; cur[u] = 0;
            if (u != s) u = e[p[u]].u;
        }
    }
    return flow;
}

void solve() {
    memset(cs, c = f = 0, sizeof(cs)); memset(ct, 0, sizeof(ct));
    int s, t, x; cin >> s >> t;
    for (int i=n+1; i>=0; --i) g[i].clear();
    while (m--) {
        int u, v, l, r; cin >> u >> v >> l >> r; cs[v] += l; ct[u] += l; f += l;
        if (l < r) add_edge(u, v, r-l);
    }
    x = c; add_edge(t, s, INF);
    for (int i=1; i<=n; ++i) {
        if (cs[i]) add_edge(0, i, cs[i]);
        if (ct[i]) add_edge(i, n+1, ct[i]);
    }
    if (max_flow(0, n+1, n+2) == f) {
        int ans = e[x].flow; e[x].cap = e[x].flow = e[x^1].flow = 0;
        cout << ans - max_flow(t, s, n+2) << endl;
    } else cout << "please go home to sleep" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) solve();
    return 0;
}