/**
 * UVa1440/LA4597
 * 滑雪场地检查
 * NEERC 2009
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 10800
#define N 104
struct edge {int u, v, cap, flow;} e[M];
int g[N][N], q[N], p[N], d[N], cur[N], num[N+1], cnt[N], cs[N], ct[N], c, n; bool vis[N];

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

int max_flow(int s, int t, int n) {
    int flow = 0, u = s;
    for (int i=0; i<n; ++i) d[i] = n;
    if (!bfs(s, t)) return 0;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<n; ++i) ++num[d[i]];
    while (d[s] < n) {
        if (u == t) {
            int a = M;
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
            int m = n-1;
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
    int s = 0, t = n+1, f = 0; memset(cnt, c = 0, sizeof(cnt)); memset(cs, 0, sizeof(cs)); memset(ct, 0, sizeof(ct));
    for (int u=1; u<=n; ++u) {
        int k, v; cin >> k;
        if (!k) continue;
        add_edge(s, u, M);
        while (k--) cin >> v, ++f, ++cs[v], ++ct[u], add_edge(u, v, M);
    }
    int x = c; add_edge(t, s, M); s = t+1; t = s+1;
    for (int i=0; i<s; ++i) {
        if (cs[i]) add_edge(i, s-1, M), add_edge(s, i, cs[i]);
        if (ct[i]) add_edge(i, t, ct[i]);
    }
    max_flow(s, t, t+1); f = e[x].flow; e[x].cap = e[x].flow = e[x^1].flow = 0;
    cout << f - max_flow(s-1, 0, t+1) << endl;
    for (int i=0; i<cnt[0]; ++i) {
        edge &ee = e[g[0][i]];
        if (ee.v > n || !ee.flow) continue;
        while (ee.flow) {
            t = 0; --ee.flow;
            for (int u = ee.v; u != s-1;) {
                p[t++] = u;
                for (int j=0; j<cnt[u]; ++j) if (~g[u][j]&1) {
                    edge &eg = e[g[u][j]];
                    if (eg.v > 0 && eg.v < s && eg.flow >= 0) {
                        --eg.flow; u = eg.v; break;
                    }
                }
            }
            for (int j=1; j<t; ++j) cout << p[j-1] << ' ';
            cout << p[t-1] << endl;
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n) solve();
    return 0;
}