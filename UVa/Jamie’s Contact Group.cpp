/**
 * UVa1345/LA3268
 * 号码簿分组
 * Shanghai 2004
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 1004000
#define N 1502
struct edge {int u, v, cap, flow;} e[M];
int g[N][1002], q[N], p[N], d[N], cur[N], num[N], cnt[N], c, m, n; bool vis[N]; char _[17];

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
    int cc = 0, u = s;
    if (!bfs(s, t)) return 0;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    while (d[s] <= t) {
        if (u == t) {
            int a = n;
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

int solve() {
    int s = 0, t = m+n+1, l = (n+m-1)/m, r = 0; memset(cnt, c = 0, sizeof(cnt)); memset(d, 0, sizeof(d));
    for (int i=1; i<=n; ++i) {
        cin >> _; add_edge(s, i, 1);
        while (cin.peek()==' ') {
            int j; cin >> j; ++d[++j]; add_edge(i, j+n, 1);
        }
    }
    for (int j=1; j<=m; ++j) r = max(r, d[j]), add_edge(j+n, t, 1);
    while (l < r) {
        int x = (l+r) >> 1;
        for (int i=0; i<c; ++i) {
            e[i].flow = 0;
            if (e[i].v == t) e[i].cap = x;
        }
        max_flow(s, t) == n ? r = x : l = x+1;
    }
    return r;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m && n) cout << solve() << endl;
    return 0;
}