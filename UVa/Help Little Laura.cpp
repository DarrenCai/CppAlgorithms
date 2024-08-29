/**
 * UVa1659/LA4030
 * 帮助小罗拉
 * Beijing 2007
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
using namespace std;

#define N 102
#define M 1780
struct edge {int u, v, cap, flow; double cost;} e[M];
int g0[N][N], cnt0[N], x[N], y[N], n, s, t, kase = 0;
int g[N][N], q[M*N], cnt[N], a[N], p[N], c; double d[N], cc; bool vis[N];

void add_edge(int u, int v, int cap, double cc) {
    e[c] = {u, v, cap, 0, cc}; g[u][cnt[u]++] = c++; e[c] = {v, u, 0, 0, -cc}; g[v][cnt[v]++] = c++;
}

double solve() {
    cin >> s >> t;
    memset(cnt0, 0, sizeof(cnt0)); memset(a, cc = 0, sizeof(a)); memset(cnt, c=0, sizeof(cnt));
    for (int i=1; i<=n; ++i) {
        cin >> x[i] >> y[i];
        int v; while (cin>>v && v) g0[i][cnt0[i]++] = v;
    }
    for (int u=1; u<=n; ++u) for (int i=0; i<cnt0[u]; ++i) {
        int v = g0[u][i]; double d = t-s*sqrt((x[u]-x[v])*(x[u]-x[v])+(y[u]-y[v])*(y[u]-y[v]));
        if (d < 0) {
            cc -= d; ++a[v]; --a[u]; add_edge(v, u, 1, -d);
        } else add_edge(u, v, 1, d);
    }
    s = 0; t = n+1;
    for (int u=1; u<=n; ++u) if (a[u] != 0) a[u] > 0 ? add_edge(s, u, a[u], 0.) : add_edge(u, t, -a[u], 0.);
    while (true) {
        for (int i=0; i<=t; ++i) d[i] = 1e39;
        memset(vis, 0, sizeof(vis)); d[s] = 0.; q[0] = s; a[s] = 1;
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
        if (d[t] >= 1e39) break;
        cc -= d[t];
        for (int u=t; u!=s; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(2);
    while (cin>>n && n) cout << "Case " << ++kase << ": " << max(solve(), 0.) << endl;
    return 0;
}