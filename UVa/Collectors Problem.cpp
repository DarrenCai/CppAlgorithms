/**
 * UVa10779
 * 收集者的难题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 11
#define N 26
#define T 546
struct edge {int u, v, cap, flow;} e[M*N*N<<1];
int g[T][N<<1], q[T], p[T], d[T], cur[T], num[T], cnt[T], cc[M][N], c, m, n, t; bool vis[T];

void add_edge(int u, int v, int cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

bool bfs() {
    memset(vis, 0, sizeof(vis)); q[0] = t; d[t] = 0; vis[t] = true;
    int head = 0, tail = 1;
    while (head < tail) {
        int v = q[head++];
        for (int i=0; i<cnt[v]; ++i) {
            const edge& ee = e[g[v][i]^1];
            if (!vis[ee.u] && ee.cap > ee.flow) vis[ee.u] = true, d[ee.u] = d[v] + 1, q[tail++] = ee.u;
        }
    }
    return vis[0];
}

int max_flow() {
    if (!bfs()) return 0;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    int flow = 0, u = 0;
    while (d[0] <= t) {
        if (u == t) {
            int a = N<<1;
            for (int v=t; v!=0; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
            for (int v=t; v!=0; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
            flow += a; u = 0;
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
            for (int i=0; i<cnt[u]; i++) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow) m = min(m, d[ee.v]);
            }
            if (--num[d[u]] == 0) break;
            ++num[d[u] = m + 1]; cur[u] = 0;
            if (u != 0) u = e[p[u]].u;
        }
    }
    return flow;
}

int solve() {
    cin >> n >> m; memset(cc, 0, sizeof(cc));
    for (int i=0; i<n; ++i) {
        int k, x; cin >> k;
        while (k--) cin >> x, ++cc[i][x];
    }
    int ans = 0; t = (2*n-1)*m+1; memset(cnt, c = 0, sizeof(cnt));
    for (int i=1; i<=m; ++i) {
        if (cc[0][i]) ++ans;
        else add_edge(i, t, 1);
        if (cc[0][i] > 1) add_edge(0, i, cc[0][i]-1);
    }
    for (int i=1; i<n; ++i) for (int a=1; a<=m; ++a)
        if (!cc[i][a]) {
            add_edge(a, (2*i-1)*m+a, 1);
            for (int b=1; b<=m; ++b) if (cc[i][b] > 1) add_edge((2*i-1)*m+a, 2*i*m+b, 1);
        } else if (cc[i][a] > 1) add_edge(2*i*m+a, a, cc[i][a]-1);
    return ans + max_flow();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) cout << "Case #" << k << ": " << solve() << endl;
    return 0;
}