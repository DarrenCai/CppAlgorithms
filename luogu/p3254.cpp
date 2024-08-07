/**
 * P3254 圆桌问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 422
#define T 82000
struct edge {int u, v, cap, flow;} e[T];
int g[N][N], q[N], p[N], d[N], cur[N], num[N], cnt[N], c, m, n; bool vis[N];

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

void solve() {
    memset(cnt, c = 0, sizeof(cnt));
    int s = 0, t = m+n+1, cc = 0, tt = 0, u = s;
    for (int i=1, r; i<=m; ++i) {
        cin >> r; tt += r; add_edge(s, i, r);
        for (int j=1; j<=n; ++j) add_edge(i, m+j, 1);
    }
    for (int i=1, x; i<=n; ++i) cin >> x, add_edge(m+i, t, x);
    bfs(s, t);
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    while (d[s] <= t) {
        if (u == t) {
            int a = 1;
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
    if (cc == tt) {
        cout << 1 << endl;
        for (int i=1; i<=m; ++i) {
            for (int j=0, k=0; j<cnt[i]; ++j) {
                const edge &ee = e[g[i][j]];
                if (ee.v != s && ee.flow) {
                    if (k++) cout << ' ';
                    cout << ee.v-m;
                }
            }
            cout << endl;
        }
    } else cout << 0 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> m >> n) solve();
    return 0;
}