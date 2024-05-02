/**
 * UVa11090
 * 在环中
 */

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

#define INF 20000000
#define N 52
struct {int v; double w;} g[N][N]; int w[N][N], c[N], f[N], cnt[N], q[N*N], m, n, kase = 0; double d[N];

bool cycle() {
    int head = 0, tail = n;
    for (int i=1; i<=n; ++i) cnt[i] = d[i] = 0, f[i] = 1, q[i-1] = i;
    while (head < tail) {
        int u = q[head++]; f[u] = 0;
        for (int i=0; i<c[u]; ++i) {
            int v = g[u][i].v; double d1 = d[u] + g[u][i].w;
            if (d[v] > d1) {
                d[v] = d1;
                if (++cnt[v] >= n) return true;
                if (!f[v]) q[tail++] = v, f[v] = 1;
            }
        }
    }
    return false;
}

bool cycle(double x) {
    for (int u=1; u<=n; ++u) for (int i=0; i<c[u]; ++i) g[u][i].w -= x;
    bool r = cycle();
    for (int u=1; u<=n; ++u) for (int i=0; i<c[u]; ++i) g[u][i].w += x;
    return r;
}

void solve() {
    memset(w, 31, sizeof(w)); memset(c, 0, sizeof(c));
    cin >> n >> m;
    int x = 0;
    while (m--) {
        int u, v, z; cin >> u >> v >> z; x = max(x, z);
        if (w[u][v] > INF) g[u][c[u]++].v = v;
        if (z < w[u][v]) w[u][v] = z;
    }
    for (int u=1; u<=n; ++u) for (int i=0; i<c[u]; ++i) g[u][i].w = w[u][g[u][i].v];
    if (cycle(x + 1e-3))  {
        double l = 0., r = x;
        while (l + 1e-3 < r) {
            double m = (l+r) / 2.;
            cycle(m) ? r = m : l = m;
        }
        cout << "Case #" << ++kase << ": " << l << endl;
    } else cout << "Case #" << ++kase << ": No cycle found." << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(2);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}