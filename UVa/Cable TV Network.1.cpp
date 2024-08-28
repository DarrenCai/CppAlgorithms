/**
 * UVa1660/LA3031
 * 电视网络
 * SEERC 2004
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 102
struct edge {int u, v, cap, flow;} e[N*N>>1];
int g[N][N>>1], q[N], p[N], d[N], cur[N], num[N], cnt[N], c, m, n; bool vis[N];

void add_edge(int u, int v, int cap) {
    e[c] = {u, v, cap, 0}; g[u][cnt[u]++] = c++; e[c] = {v, u, 0, 0}; g[v][cnt[v]++] = c++;
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
    for (int i=0; i<c; ++i) e[i].flow = 0;
    if (!bfs(s, t)) return 0;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    int u = s, flow = 0, n1 = n<<1;
    for (int i=0; i<n1; ++i) ++num[d[i]];
    while (d[s] < n1) {
        if (u == t) {
            int a = n;
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
            int m = n1 - 1;
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

int solve() {
    int ans = n; char _; memset(cnt, c = 0, sizeof(cnt));
    for (int i=0; i<n; ++i) add_edge(i, i+n, 1);
    for (int i=0, u, v; i<m; ++i) cin >> _ >> u >> _ >> v >> _, add_edge(u+n, v, n), add_edge(v+n, u, n);
    for (int i=0; i<n; ++i) for (int j=i+1; j<n; ++j) ans = min(ans, max_flow(i+n, j));
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) cout << solve() << endl;
    return 0;
}