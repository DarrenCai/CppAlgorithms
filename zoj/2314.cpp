/**
 * zoj-2314 Reactor Cooling
 * https://vjudge.net/problem/ZOJ-2314
 * https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?problemSetProblemId=91827365813&page=13
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 0x7f7f7f7f
#define N 202
struct edge {int u, v, cap, flow;} e[N*N];
int g[N][N], q[N], p[N], d[N], cur[N], num[N], cnt[N], cs[N], ct[N], h[N*N>>1], b[N*N>>1], c, m, n, f; bool vis[N];

void add_edge(int u, int v, int cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

bool bfs(int s, int t) {
    memset(vis, 0, sizeof(vis)); memset(d, 0, sizeof(d)); q[0] = t; d[t] = 0; vis[t] = true;
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

int max_flow(int s, int t) {
    int flow = 0, u = s;
    if (!bfs(s, t)) return 0;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    while (d[s] <= t) {
        if (u == t) {
            int a = INF;
            for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
            for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
            flow += a; u = s;
        }
        int ok = 0;
        for (int i=cur[u]; i<cnt[u]; ++i) {
            const edge& ee = e[g[u][i]];
            if (ee.cap > ee.flow && d[u] == d[ee.v] + 1) {
                ok = 1; p[ee.v] = g[u][i]; cur[u] = i; u = ee.v;
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
    return flow;
}

void solve() {
    cin >> n >> m; memset(cnt, c = f = 0, sizeof(cnt)); memset(cs, 0, sizeof(cs)); memset(ct, 0, sizeof(ct));
    int s = 0, t = n+1;
    for (int i=0; i<m; ++i) {
        int u, v, s; cin >> u >> v >> b[i] >> s;
        f += b[i]; cs[v] += b[i]; ct[u] += b[i]; h[i] = c; add_edge(u, v, s-b[i]);
    }
    for (int i=1; i<=n; ++i) {
        if (cs[i]) add_edge(s, i, cs[i]);
        if (ct[i]) add_edge(i, t, ct[i]);
    }
    if (max_flow(s, t) == f) {
        cout << "YES" << endl;
        for (int i=0; i<m; ++i) cout << e[h[i]].flow + b[i] << endl;
    } else cout << "NO" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        solve();
        if (t) cout << endl;
    }
    return 0;
}