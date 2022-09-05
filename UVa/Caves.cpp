/**
 * UVa1407/LA4015
 * 洞穴
 * ChengDu 2007
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 520
int g[N][N], s[N][N], c[N], d[N][2][N], n, kase = 0;

int dfs(int u) {
    int cc = 0;
    d[u][0][0] = d[u][1][0] = 0;
    for (int i=0; i<c[u]; ++i) {
        int v = g[u][i], x = dfs(v);
        cc += 1 + x;
        for (int j=cc; j>0; --j) for (int k=min(x, j-1); k>=0; --k) {
            int k1 = j-k-1;
            d[u][0][j] = min(d[u][0][j], d[u][0][k1] + 2*s[u][v] + d[v][1][k]);
            d[u][0][j] = min(d[u][0][j], d[u][1][k1] + s[u][v] + d[v][0][k]);
            d[u][1][j] = min(d[u][1][j], d[u][1][k1] + 2*s[u][v] + d[v][1][k]);
        }
    }
    return cc;
}

void solve() {
    memset(c, 0, sizeof(c));
    int root = n*(n-1)/2;
    for (int i=1; i<n; ++i) {
        int u, v; cin >> v >> u >> s[u][v];
        g[u][c[u]++] = v;
        root -= v;
    }
    memset(d, 1, sizeof(d));
    dfs(root);
    int q; cin >> q;
    cout << "Case " << ++kase << ':' << endl;
    while (q--) {
        int x; cin >> x;
        cout << upper_bound(d[root][0], d[root][0]+n, x) - d[root][0] << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) solve();
    return 0;
}