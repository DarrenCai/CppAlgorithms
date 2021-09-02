/**
 * UVa10048
 * 噪音恐惧症
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 105
int g[N][N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n, m, q, kase=0;
    while (cin>>n>>m>>q && n && q) {
        ++n;
        memset(g, -1, sizeof(g));
        for (short i=0; i<m; ++i) {
            short u, v; int w; cin >> u >> v >> w;
            g[u][v] = g[v][u] = w;
        }
        for (short k=1; k<n; ++k) for (short i=1; i<n; ++i) for (short j=1; j<n; ++j) if (g[i][k]>-1 && g[k][j]>-1)
            g[i][j] = g[i][j]>-1 ? min(g[i][j], max(g[i][k], g[k][j])) : max(g[i][k], g[k][j]);
        if (kase) cout << endl;
        cout << "Case #" << ++kase << endl;
        while (q--) {
            short u, v; cin >> u >> v;
            g[u][v] > -1 ? cout << g[u][v] << endl : cout << "no path" << endl;
        }
    }
    return 0;
}