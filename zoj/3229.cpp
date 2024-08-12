/**
 * zoj-3229 Shoot the Bullet
 * https://vjudge.net/problem/ZOJ-3229
 * https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?problemSetProblemId=91827367941
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 0x7f7f7f7f
#define N 1369
struct edge {int u, v, cap, flow;} e[60*N];
int g[N][N], b[365][N], q[N], p[N], d[N], cur[N], num[N], cnt[N], cs[N], ct[N], c, m, n, f; bool vis[N];

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

int max_flow(int s, int t, int n) {
    int flow = 0, u = s;
    if (!bfs(s, t)) return 0;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<n; ++i) ++num[d[i]];
    while (d[s] < n) {
        if (u == t) {
            int a = INF;
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
    memset(cnt, c = f = 0, sizeof(cnt)); memset(cs, 0, sizeof(cs)); memset(ct, 0, sizeof(ct));
    int s = m+n, t = s+1;
    for (int i=0, x; i<m; ++i) cin >> x, f += x, cs[i] += x, ct[s] += x, add_edge(s, i, INF);
    for (int i=0; i<n; ++i) {
        int c, d; cin >> c >> d; add_edge(m+i, t, d);
        while (c--) {
            int k, l, r; cin >> k >> l >> r; f += l; cs[m+i] += l; ct[k] += l; b[i][k] = l; add_edge(k, m+i, r-l);
        }
    }
    add_edge(t, s, INF); s = t+1; t = s+1;
    for (int i=s-2; i>=0; --i) {
        if (cs[i]) add_edge(s, i, cs[i]);
        if (ct[i]) add_edge(i, t, ct[i]);
    }
    if (max_flow(s, t, t+1) == f) {
        cout << max_flow(s-2, t-2, t+1) << endl;
        for (int i=0; i<n; ++i) for (int j=0, k=cnt[m+i]; j<k; ++j) {
            const edge &ee = e[g[m+i][j]^1];
            if (ee.u < m) cout << b[i][ee.u] + ee.flow << endl;
        }
    } else cout << -1 << endl;
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) solve();
    return 0;
}