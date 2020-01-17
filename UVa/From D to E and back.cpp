/**
 * UVa11175
 * 向图D和E
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 301
bool g[N][N], c[N][N]; int m;

bool judge() {
    memset(c, 0, sizeof(c));
    for (int v=0; v<m; ++v) for (int u1=0; u1<m; ++u1)
        if (g[u1][v]) for (int u2=0; u2<m; ++u2) if (g[u2][v]) c[u1][u2] = true;
    for (int u1=0; u1<m; ++u1) for (int u2=0; u2<m; ++u2) if (c[u1][u2])
        for (int v=0; v<m; ++v) if (g[u1][v] && !g[u2][v]) return false;
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin>>t;
    for (int i=1; i<=t; ++i) {
        int k; cin >> m >> k; memset(g, 0, sizeof(g));
        for (int j=0; j<k; ++j) {
            int u, v; cin >> u >> v; g[u][v] = true;
        }
        cout << "Case #" << i << ": " << (judge() ? "Yes" : "No") << endl;
    }
    return 0;
}