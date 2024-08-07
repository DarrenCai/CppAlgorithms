/**
 * P2763 试题库问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1024
struct edge {int u, v, cap, flow;} e[40*N];
int g[N][N], q[N], p[N], d[N], cur[N], num[N], cnt[N], c, m, n, k; bool vis[N];

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

void solve() {
    int s = m = 0, t = k+n+1, flow = 0, u = s; memset(cnt, c = 0, sizeof(cnt));
    for (int i=1, x; i<=k; ++i) cin >> x, m += x, add_edge(s, i, x);
    for (int i=1; i<=n; ++i) {
        int p, x; cin >> p; add_edge(i+k, t, 1);
        while (p--) cin >> x, add_edge(x, i+k, 1);
    }
    bfs(s, t); memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    while (d[s] <= t) {
        if (u == t) {
            int a = m;
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
    if (flow == m) {
        for (int i=1; i<=k; ++i) {
            cout << i << ':';
            for (int j=0; j<cnt[i]; ++j) {
                const edge &ee = e[g[i][j]];
                if (ee.v != s && ee.flow) cout << ' ' << ee.v - k;
            }
            cout << endl;
        }
    } else cout << "No Solution!" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> k >> n) solve();
    return 0;
}