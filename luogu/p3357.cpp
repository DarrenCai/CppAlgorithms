/**
 * P3357 最长k可重线段集问题
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

#define N 2002
struct edge {int u, v, cap, flow; long long cost;} e[3*N]; long long d[N];
int g[N][N>>1], q[3*N*N], a[N], p[N], cnt[N], xl[N], yl[N], xr[N], yr[N], x[N], c, m, n, k; bool vis[N];

void add_edge(int u, int v, int cap, long long cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int solve() {
    for (int i=m=0; i<n; ++i) cin >> xl[i] >> yl[i] >> xr[i] >> yr[i], x[m++] = xl[i], x[m++] = xr[i];
    sort(x, x+m); m = unique(x, x+m) - x; memset(cnt, c = 0, sizeof(cnt));
    int s = 0, t = 2*m; long long cc = 0;
    for (int i=0; i<m; ++i) add_edge(i, i+m, k, 0), add_edge(i+m, i+1==m ? t : i+1, k, 0);
    for (int i=0; i<n; ++i) {
        double dx = xl[i]-double(xr[i]), dy = yl[i]-double(yr[i]);
        int l = lower_bound(x, x+m, xl[i]) - x, r = lower_bound(x, x+m, xr[i]) - x;
        if (l == r) {
            add_edge(l, m+l, 1, -sqrt(dx*dx + dy*dy));
            continue;
        }
        if (l > r) l = l+r, r = l-r, l = l-r;
        add_edge(m+l, r, 1, -sqrt(dx*dx + dy*dy));
    }
    while (true) {
        memset(d, 1, sizeof(d)); memset(vis, 0, sizeof(vis)); d[s] = 0; q[0] = s; a[s] = k;
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
        if (d[t] >= 0) break;
        cc -= d[t] * a[t];
        for (int u=t; u!=s; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> k) cout << solve() << endl;
    return 0;
}