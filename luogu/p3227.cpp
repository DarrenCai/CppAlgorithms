/**
 * P3227 [HNOI2013] 切糕
 */

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define INF 1010
#define N 74088
struct edge {int u, v, cap, flow;}; vector<edge> e; vector<int> g[N];
int q[N], p[N], d[N], cur[N], num[N], P, Q, R, D; bool vis[N];

void add_edge(int u, int v, int cap) {
    g[u].push_back(e.size()); e.push_back({u, v, cap, 0});
    g[v].push_back(e.size()); e.push_back({v, u, 0, 0});
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

int solve() {
    int s = 0, t = P*Q*R + 1, cc = 0; e.clear();
    for (int i=0; i<N; ++i) g[i].clear();
    for (int z=0; z<R; ++z) for (int x=1; x<=P; ++x) for (int y=1; y<=Q; ++y) {
        int u = P*Q*z + (x-1)*Q + y, v; cin >> v;
        add_edge(z ? u-P*Q : s, u, v);
        if (z < D) continue;
        if (x > 1) add_edge(u, u - P*Q*D - Q, INF);
        if (x < P) add_edge(u, u - P*Q*D + Q, INF);
        if (y > 1) add_edge(u, u - P*Q*D - 1, INF);
        if (y < Q) add_edge(u, u - P*Q*D + 1, INF);
    }
    for (int x=1; x<=P; ++x) for (int y=1; y<=Q; ++y) add_edge(P*Q*(R-1) + (x-1)*Q + y, t, INF);
    if (!bfs(s, t)) return 0;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    int u = s;
    while (d[s] <= t) {
        if (u == t) {
            int a = INF;
            for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
            for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
            cc += a; u = s;
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
            for (int i=0; i<g[u].size(); ++i) {
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
    while (cin >> P >> Q >> R >> D) cout << solve() << endl;
    return 0;
}