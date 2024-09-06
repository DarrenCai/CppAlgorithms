/**
 * UVa1104/LA5131
 * 芯片难题
 * World Finals 2011
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 3440
#define N 82
struct edge {int u, v, cap, flow, cost;} e[M];
int g[N][N], q[M*N], a[N], d[N], p[N], cnt[N], hu[N], c, n, h, b, kase = 0; bool vis[N]; 

void add_edge(int u, int v, int cap, int cc) {
    e[c] = {u, v, cap, 0, cc}; g[u][cnt[u]++] = c++; e[c] = {v, u, 0, 0, -cc}; g[v][cnt[v]++] = c++;
}

int solve() {
    int s = 0, t = 2*n+1, f = 0, c0 = 0, cc = -1;
    memset(cnt, c = 0, sizeof(cnt)); memset(a, 0, sizeof(a));
    for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) {
        char x; cin >> x;
        if (x == 'C') ++a[j+n], ++a[i], ++f, ++c0;
        else if (x == '.') ++a[j+n], ++a[i], ++f, add_edge(i, j+n, 1, 1);
    }
    for (int i=1; i<=n; ++i) {
        hu[i] = c; add_edge(i, i+n, n, 0);
        if (a[i]) add_edge(s, i, a[i], 0);
        if (a[i+n]) add_edge(i+n, t, a[i+n], 0);
    }
    for (int k=0; k<=n; ++k) {
        for (int i=0; i<c; ++i) e[i].flow = 0;
        for (int i=1; i<=n; ++i) e[hu[i]].cap = k;
        int flow = f, cost = f;
        while (true) {
            memset(d, 1, sizeof(d)); memset(vis, 0, sizeof(vis)); d[s] = 0; q[0] = s; a[s] = M;
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
            if (d[t] > M) break;
            flow -= a[t]; cost -= d[t] * a[t];
            for (int u=t; u!=s; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
        }
        if (flow || cost*h < k*b) continue;
        cc = max(cc, cost - c0);
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> h >> b && n) {
        int cc = solve();
        cout << "Case " << ++kase << ": ";
        cc < 0 ? cout << "impossible" << endl : cout << cc << endl;
    }
    return 0;
}