/**
 * UVa12125/LA3972
 * 企鹅的游行
 * NWERC 2007
 */

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

#define M 20400
#define N 202
struct edge {int u, v, cap, flow;} e[M];
int g[N][N], q[N], p[N], d[N], cur[N], num[N+1], cnt[N], a[N], c, n; bool vis[N];

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
    double ds; int s = 0, f = 0, cc = 0; cin >> n >> ds; memset(cnt, c = 0, sizeof(cnt));
    for (int i=1; i<=n; ++i) {
        int w; cin >> p[i] >> q[i] >> w >> d[i]; f += w; add_edge(i, i+n, d[i]);
        if (w) add_edge(s, i, w);
    }
    for (int i=1; i<=n; ++i) for (int j=i+1; j<=n; ++j) {
        double t = sqrt((p[i]-p[j])*(p[i]-p[j]) + (q[i]-q[j])*(q[i]-q[j]));
        if (t > ds) continue;
        add_edge(i+n, j, d[i]); add_edge(j+n, i, d[j]);
    }
    for (int i=1; i<=n; ++i) {
        for (int j=0; j<c; ++j) e[j].flow = 0;
        if (max_flow(s, i, 2*n+1) == f) a[cc++] = i-1;
    }
    if (cc) {
        for (int i=1; i<cc; ++i) cout << a[i-1] << ' ';
        cout << a[cc-1] << endl;
    } else cout << -1 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}