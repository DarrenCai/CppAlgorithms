/**
 * UVa1048/LA3561
 * 低价空中旅行
 * World Finals >> 2006 - San Antonio
 */

#include <iostream>
#include <cstring>
using namespace std;

#define T 21
#define M 11
#define N 202
int d[M][N], a[T][M], w[T], c[T], b[M], id[N], m, n, t, x, kase = 0; struct {int k, v, i;} ans[M][N];

int find(int v) {
    for (int i=0; i<x; ++i) if (id[i] == v) return i;
    id[x] = v;
    return x++;
}

int bfs() {
    cin >> m;
    for (int i=0, v; i<m; ++i) cin >> v, b[i] = find(v);
    memset(d, -1, sizeof(d)); d[1][b[0]] = 0;
    for (int i=1, ch=1; i<m; ++i, ch=1) while (ch) {
        for (int j=ch=0; j<x; ++j) if (d[i][j] >= 0) for (int k=1; k<=t; ++k) if (a[k][0] == j)
        for (int q=1, s=i, v; q<c[k] && s<m; ++q) {
            if ((v = a[k][q]) == b[s]) ++s;
            int &r = d[s][v], g = d[i][j] + w[k];
            if (r < 0 || g < r) r = g, ans[s][v] = {i, j, k}, ch = 1;
        }
    }
    return d[m][b[m-1]];
}

void path(int k, int v) {
    if (ans[k][v].k > 1 || ans[k][v].v != b[0]) path(ans[k][v].k, ans[k][v].v);
    cout << ' ' << ans[k][v].i;
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
        path(m, b[m-1]); cout << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> t && t) solve();
    return 0;
}