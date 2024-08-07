/**
 * P3159 交换棋子
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 20000000
#define N 802
struct edge {int u, v, cap, flow, cost;} e[12*N]; char s1[22][22], s2[22][22], s3[22][22];
int g[N][N>>1], q[12*N*N], a[N], d[N], p[N], cnt[N], c, m, n; bool vis[N];

void add_edge(int u, int v, int cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int solve() {
    for (int i=1; i<=n; ++i) cin >> s1[i]+1;
    for (int i=1; i<=n; ++i) cin >> s2[i]+1;
    for (int i=1; i<=n; ++i) cin >> s3[i]+1;
    memset(cnt, c = 0, sizeof(cnt));
    int s = 0, t = 2*m*n+1, f = 0, cc = 0;
    for (int i=1, x=1; i<=n; ++i) for (int j=1; j<=m; ++j, ++x) {
        int k = s3[i][j] - '0', y = x+m*n;
        if (s1[i][j] == '1') {
            if (s2[i][j] == '0') add_edge(s, x, 1, 0), ++f;
        } else if (s2[i][j] == '1') add_edge(y, t, 1, 0), --f;
        add_edge(x, y, k&1 && s1[i][j] != s2[i][j] ? (k+1)>>1 : k>>1, 0);
        if (i > 1) {
            add_edge(y, x-m, INF, 1);
            if (j > 1) add_edge(y, x-m-1, INF, 1);
            if (j < m) add_edge(y, x-m+1, INF, 1);
        }
        if (j > 1) add_edge(y, x-1, INF, 1);
        if (j < m) add_edge(y, x+1, INF, 1);
        if (i < n) {
            add_edge(y, x+m, INF, 1);
            if (j > 1) add_edge(y, x+m-1, INF, 1);
            if (j < m) add_edge(y, x+m+1, INF, 1);
        }
    }
    if (f) return -1;
    while (true) {
        memset(d, 0x7f, sizeof(d)); memset(vis, 0, sizeof(vis));
        d[s] = 0; q[0] = s; a[s] = INF;
        int head = 0, tail = 1;
        while (head < tail) {
            short u = q[head++]; vis[u] = false;
            for (short i=0; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow && d[ee.v] > d[u]+ee.cost) {
                    d[ee.v] = d[u]+ee.cost;
                    p[ee.v] = g[u][i];
                    a[ee.v] = min(a[u], ee.cap-ee.flow);
                    if (!vis[ee.v]) vis[q[tail++] = ee.v] = true;
                }
            }
        }
        if (d[t] >= INF) return cc;
        cc += d[t] * a[t];
        for (short u=t; u!=s; u=e[p[u]].u) {
            e[p[u]].flow += a[t];
            e[p[u]^1].flow -= a[t];
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