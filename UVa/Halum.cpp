/**
 * UVa11478
 * Halum 操作
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 10010
#define N 502
int g[N][N], w[N][N], q[N*N], c[N], cnt[N], d[N], f[N], m, n;

bool cycle() {
    int head = 0, tail = n;
    for (int i=1; i<=n; ++i) d[i] = cnt[i] = 0, f[i] = 1, q[i-1] = i;
    while (head < tail) {
        int u = q[head++]; f[u] = 0;
        for (int i=0; i<c[u]; ++i) {
            int v = g[u][i], d1 = d[u] + w[u][v];
            if (d[v] > d1) {
                d[v] = d1;
                if (++cnt[v] == n) return true;
                if (!f[v]) q[tail++] = v, f[v] = 1;
            }
        }
    }
    return false;
}

bool cycle(int x) {
    for (int u=1; u<=n; ++u) for (int i=0; i<c[u]; ++i) w[u][g[u][i]] -= x;
    bool r = cycle();
    for (int u=1; u<=n; ++u) for (int i=0; i<c[u]; ++i) w[u][g[u][i]] += x;
    return r;
}

void solve() {
    memset(c, 0, sizeof(c)); memset(w, 1, sizeof(w));
    int l = 0, r = -INF;
    while (m--) {
        int u, v, z; cin >> u >> v >> z;
        if (w[u][v] >= INF) g[u][c[u]++] = v;
        w[u][v] = min(w[u][v], z); r = max(r, z);
    }
    if (cycle(r+1)) {
        while (l < r) cycle(m = (l+r+1)>>1) ? r = m-1 : l = m;
        r > 0 ? cout << r << endl : cout << "No Solution" << endl;
    } else cout << "Infinite" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) solve();
}