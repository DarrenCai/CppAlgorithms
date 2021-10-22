/**
 * UVa1660
 * 电视网络
 */

#include <iostream>
using namespace std;

#define N 60
struct {short u, v;} e[N*N>>1]; short c[N], cc[N], p[N], g[N][N], n, m;

short find(short x) {
    return p[x]==x ? x : p[x] = find(p[x]);
}

short check() {
    short t = 0;
    for (short i=0; i<n; ++i) if (c[i]>=0 && find(i)==i) ++t;
    return t;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) {
        for (short i=0; i<n; ++i) cc[i] = 0, p[i] = i;
        for (short i=0; i<m; ++i) {
            short u, v; char t;
            cin >> t >> u >> t >> v >> t;
            g[u][cc[u]++] = v; g[v][cc[v]++] = u;
            e[i].u = u; e[i].v = v;
            p[find(u)] = find(v);
        }
        for (short i=0; i<n; ++i) c[i] = cc[i];
        short ans = 0;
        while (check() == 1) {
            short cx = N, cy = -1, x, y;
            for (short i=0; i<n; ++i) if (c[i] >= 0) {
                if (cx > c[i]) cx = c[y = x = i];
                p[i] = i;
            }
            for (short i=0; i<cc[x]; ++i) if (c[g[x][i]] > cy) cy = c[y = g[x][i]];
            for (short i=0; i<cc[y]; ++i) --c[g[y][i]];
            c[y] = -1;
            for (short i=0; i<m; ++i) {
                short u = e[i].u, v = e[i].v;
                if (c[u]>0 && c[v]>0) p[find(u)] = find(v);
            }
            ++ ans;
        }
        cout << ans << endl;
    }
}