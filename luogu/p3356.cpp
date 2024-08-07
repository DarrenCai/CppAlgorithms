/**
 * P3356 火星探险问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 2452
struct edge {int u, v, cap, flow, cost;} e[6*N];
int x[36][36], g[N][6], q[6*N*N], a[N], d[N], p[N], cnt[N], c, n, w, h; bool vis[N];

void add_edge(int u, int v, int cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

void move(int k, int u) {
    for (int i=0, d=w*h; i<cnt[u]; ++i) {
        edge &ee = e[g[u][i]];
        if (ee.flow > 0) {
            --ee.flow;
            if (ee.u < d) return move(k, ee.v);
            if (ee.u > d) {
                cout << k << ' ' << (ee.v == ee.u-d+1 ? 1 : 0) << endl;
                return move(k, ee.v);
            }
            break;
        }
    }
}

void solve() {
    int s = 0, t = 2*w*h+1;
    memset(cnt, c = 0, sizeof(cnt)); add_edge(s, 1, n, 0); add_edge(t-1, t, n, 0);
    for (int i=1; i<=h; ++i) for (int j=1; j<=w; ++j) cin >> x[i][j];
    for (int i=1, k=1, d=w*h; i<=h; ++i) for (int j=1; j<=w; ++j, ++k) if (x[i][j] != 1) {
        add_edge(k, k+d, n, 0);
        if (x[i][j] == 2) add_edge(k, k+d, 1, -1);
        if (j < w && x[i][j+1] != 1) add_edge(k+d, k+1, n, 0);
        if (i < h && x[i+1][j] != 1) add_edge(k+d, k+w, n, 0);
    }
    while (true) {
        memset(d, 1, sizeof(d)); memset(vis, 0, sizeof(vis));
        d[s] = 0; q[0] = s; a[s] = n;
        int head = 0, tail = 1;
        while (head < tail) {
            int u = q[head++]; vis[u] = false;
            for (int i=0; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow && d[ee.v] > d[u]+ee.cost) {
                    d[ee.v] = d[u]+ee.cost;
                    p[ee.v] = g[u][i];
                    a[ee.v] = min(a[u], ee.cap-ee.flow);
                    if (!vis[ee.v]) vis[q[tail++] = ee.v] = true;
                }
            }
        }
        if (d[t] >= n) break;
        for (int u=t; u!=s; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
    }
    for (int i=1, u; i<=n; ++i) {
        if (!e[0].flow--) break;
        move(i, 1);
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> w >> h) solve();
    return 0;
}