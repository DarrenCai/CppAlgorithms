/**
 * UVa1048/LA3561
 * 低价空中旅行
 * World Finals >> 2006 - San Antonio
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define T 21
#define M 11
#define N 202
int d[N][M], f[N][M], a[T][M], w[T], c[T], b[M], id[N], m, n, t, x, kase = 0;
struct node {int v, k;} p; struct {int v, k, i;} ans[N][M];

int find(int v) {
    for (int i=0; i<x; ++i) if (id[i] == v) return i;
    id[x] = v;
    return x++;
}

int bfs() {
    cin >> m;
    for (int i=0, v; i<m; ++i) cin >> v, b[i] = find(v);
    memset(d, 1, sizeof(d)); memset(f, 0, sizeof(f)); queue<node> q;
    for (int i=1; i<=t; ++i) if (a[i][0] == b[0]) for (int j=1, k=1, v; j<c[i] && k<m; ++j) {
        if ((v = a[i][j]) == b[k]) ++k;
        if (w[i] < d[v][k]) {
            d[v][k] = w[i]; ans[v][k] = {0, 0, i};
            if (k<m && !f[v][k]) q.push({v, k}), f[v][k] = 1;
        }
    }
    while (!q.empty()) {
        p = q.front(); q.pop();
        int v0 = p.v, k0 = p.k, g = d[v0][k0]; f[v0][k0] = 0;
        for (int i=1; i<=t; ++i) if (a[i][0] == v0) for (int j=1, k=k0, v; j<c[i] && k<m; ++j) {
            if ((v = a[i][j]) == b[k]) ++k;
            if (g + w[i] < d[v][k]) {
                d[v][k] = g + w[i]; ans[v][k] = {v0, k0, i};
                if (k<m && !f[v][k]) q.push({v, k}), f[v][k] = 1;
            }
        }
    }
    return d[b[m-1]][m];
}

void path(int v, int k) {
    if (ans[v][k].k) path(ans[v][k].v, ans[v][k].k);
    cout << ' ' << ans[v][k].i;
}

void solve() {
    x = 0;
    for (int i=1; i<=t; ++i) {
        cin >> w[i] >> c[i];
        for (int j=0, v; j<c[i]; ++j) cin >> v, a[i][j] = find(v);
    }
    cin >> n; ++kase;
    for (int i=1; i<=n; ++i) {
        cout << "Case " << kase << ", Trip " << i << ": Cost = " << bfs() << endl << "  Tickets used:";
        path(b[m-1], m); cout << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> t && t) solve();
    return 0;
}