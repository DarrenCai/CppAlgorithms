/**
 * UVa1660
 * 电视网络
 */

#include <iostream>
using namespace std;

#define N 60
short u[N*N>>1], v[N*N>>1], c[N], cc[N], p[N], g[N][N], n, m;

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
            short a, b; char t;
            cin >> t >> a >> t >> b >> t;
            g[a][cc[a]++] = b; g[b][cc[b]++] = a;
            u[i] = a; v[i] = b;
            p[find(a)] = find(b);
        }
        for (short i=0; i<n; ++i) c[i] = cc[i];
        short ans = 0;
        while (check() == 1) {
            ++ ans;
            short cx = N, cy = -1, k;
            for (short i=0; i<m; ++i) if (c[u[i]]>0 && c[v[i]]>0) {
                short a = min(c[u[i]], c[v[i]]), b = max(c[u[i]], c[v[i]]);
                if (a<cx || (a==cx && b>cy)) cx = a, cy = b, k = i;
            }
            if (cy < 0) break;
            short y = c[u[k]] == cy ? u[k] : v[k];
            for (short i=0; i<cc[y]; ++i) --c[g[y][i]];
            c[y] = -1;
            for (short i=0; i<n; ++i) p[i] = i;
            for (short i=0; i<m; ++i) if (c[u[i]]>0 && c[v[i]]>0) p[find(u[i])] = find(v[i]);
        }
        cout << ans << endl;
    }
}