/**
 * UVa10735
 * 混合图的欧拉回路
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 600
#define N 102
struct edge {int u, v, cap, flow;} e[M<<1];
int g[N][M], q[N], p[M], d[N], cur[N], num[N+1], cnt[N], u[M], v[M], h[M], c, m, n; bool vis[M];

void add_edge(int u, int v, int cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
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

void euler(int x) {
    for (int i=0, j; i<cnt[x]; ++i) if (!vis[j = g[x][i]]) vis[j] = true, euler(u[j]+v[j]-x), p[n++] = x;
}

bool solve() {
    cin >> n >> m; memset(cnt, c = 0, sizeof(cnt)); memset(d, 0, sizeof(d));
    for (int i=0; i<m; ++i) {
        char x; cin >> u[i] >> v[i] >> x; ++d[u[i]]; --d[v[i]]; h[i] = -1;
        if (x == 'U') h[i] = c, add_edge(u[i], v[i], 1);
    }
    int s = 0, t = n+1, f = 0;
    for (int i=1; i<=n; ++i) {
        if (d[i] & 1) return false;
        if (d[i] > 0) add_edge(s, i, d[i]>>1), f += d[i]>>1;
        if (d[i] < 0) add_edge(i, t, -d[i]>>1);
    }
    if (f) {
        for (int i=0; i<=t; ++i) d[i] = t+1;
        bfs(s, t); memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
        for (int i=0; i<=t; ++i) ++num[d[i]];
        for (int u=s; d[s] <= t;) {
            if (u == t) {
                int a = 1;
                for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
                for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
                f -= a; u = s;
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
    }
    if (f) return false;
    memset(cnt, n = 0, sizeof(cnt));
    for (int i=0; i<m; ++i) {
        vis[i] = false; h[i] >= 0 && e[h[i]].flow ? g[v[i]][cnt[v[i]]++] = i : g[u[i]][cnt[u[i]]++] = i;
    }
    euler(1);
    while (n--) cout << p[n] << ' ';
    cout << 1 << endl;
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        if (!solve()) cout << "No euler circuit exist" << endl;
        if (t) cout << endl;
    }
    return 0;
}