/**
 * P3355 骑士共存问题
 */

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define N 40002
struct edge {int u, v, cap, flow;} e[10*N]; vector<int> g[N];
int q[N], p[N], d[N], cur[N], num[N], c, m, n; bool f[200][200], vis[N];

void add_edge(int u, int v, int cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u].push_back(c++);
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v].push_back(c++);
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

int solve() {
    memset(f, c = 0, sizeof(f));
    int s = 0, t = n*n+1, cc = n*n-m, u = s;
    for (int i=0; i<=t; ++i) g[i].clear();
    while (m--) {
        int x, y; cin >> x >> y; f[--x][--y] = true;
    }
    for (int i=0, k=1; i<n; ++i) for (int j=0; j<n; ++j, ++k) if (!f[i][j]) {
        if ((i+j)&1) {
            add_edge(s, k, 1);
            if (i > 0) {
                if (j > 1) add_edge(k, k-2-n, 1);
                if (j+2 < n) add_edge(k, k+2-n, 1);
            }
            if (i+1 < n) {
                if (j > 1) add_edge(k, k-2+n, 1);
                if (j+2 < n) add_edge(k, k+2+n, 1);
            }
            if (i > 1) {
                if (j > 0) add_edge(k, k-1-2*n, 1);
                if (j+1 < n) add_edge(k, k+1-2*n, 1);
            }
            if (i+2 < n) {
                if (j > 0) add_edge(k, k-1+2*n, 1);
                if (j+1 < n) add_edge(k, k+1+2*n, 1);
            }
        } else add_edge(k, t, 1);
    }
    bfs(s, t);
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    while (d[s] <= t) {
        if (u == t) {
            int a = 1;
            for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
            for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
            cc -= a; u = s;
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
            int m = t;
            for (int i=g[u].size()-1; i>=0; --i) {
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
    while (cin >> n >> m) cout << solve() << endl;
    return 0;
}