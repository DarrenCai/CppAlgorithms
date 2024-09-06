/**
 * UVa1161/LA3645
 * 航程规划
 * SWERC 2004
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 10002
struct edge {int u, v, cap, flow;} e[N*N>>1]; char city[152][10];
int g[N][N>>1], q[N], p[N], d[N], cnt[N], cur[N], num[N+1], a[N], b[N], w[N], c, m, n, x, y; bool vis[N];

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

int idx() {
    cin >> city[x];
    for (int i=0; i<x; ++i) if (!strcmp(city[i], city[x])) return i;
    return x++;
}

int get_t() {
    int x; cin >> x;
    return x/100*60 + x%100;
}

int solve() {
    cin >> city[0] >> city[1]; y = get_t(); cin >> m;
    int s = 0, t = 2*m+1, u = s, cc = 0; x = 2; memset(cnt, c = 0, sizeof(cnt));
    for (int i=1; i<=m; ++i) {
        p[i] = idx(); q[i] = idx(); cin >> w[i]; a[i] = get_t(); b[i] = get_t();
        add_edge(i, i+m, w[i]);
        if (p[i] == 0) add_edge(s, i, w[i]);
        if (q[i] == 1 && b[i] <= y) add_edge(i+m, t, w[i]);
    }
    for (int i=1; i<=m; ++i) for (int j=1; j<=m; ++j) if (q[i] == p[j] && b[i]+30 <= a[j]) add_edge(i+m, j, w[i]);
    for (int i=0; i<=t; ++i) d[i] = t+1;
    if (!bfs(s, t)) return 0;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    while (d[s] <= t) {
        if (u == t) {
            int a = N;
            for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
            for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
            cc += a; u = s;
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
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n) cout << solve() << endl;
    return 0;
}