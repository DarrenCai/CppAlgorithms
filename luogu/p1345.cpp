/**
 * P1345 [USACO5.4] 奶牛的电信Telecowmunication
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 2000
#define N 202
struct edge {int u, v, cap, flow;} e[13*N];
int g[N][N>>1], q[N], p[N], d[N], cur[N], num[N], cnt[N], c, m, n, c1, c2; bool vis[N];

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

int solve() {
    memset(cnt, c = 0, sizeof(cnt));
    int s = c1, t = c2+n, cc = 0;
    for (int i=1; i<=n; ++i) add_edge(i, i+n, i==c1 || i==c2 ? INF : 1);
    while (m--) {
        int a, b; cin >> a >> b;
        if (b != c1) add_edge(a+n, b, 1);
        if (b != c2) add_edge(b+n, a, 1);
    }
    n <<= 1;
    if (!bfs(s, t)) return cc;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=1; i<=n; ++i) ++num[d[i]];
    int u = s;
    while (d[s] < n) {
        if (u == t) {
            int a = INF;
            for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
            for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
            cc += a; u = s;
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
            int m = n-1;
            for (int i=0; i<cnt[u]; i++) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow) m = min(m, d[ee.v]);
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
    while (cin >> n >> m >> c1 >> c2) cout << solve() << endl;
    return 0;
}