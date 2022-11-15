/**
 * UVa10243
 */

#include <iostream>
using namespace std;

#define N 1010
int d[N][2], g[N][N], c[N], n;

void dfs(int u = 1, int fa = 0) {
    d[u][0] = 0; d[u][1] = 1;
    for (int i=0; i<c[u]; ++i) {
        int v = g[u][i];
        if (v != fa) {
            dfs(v, u);
            d[u][1] += min(d[v][0], d[v][1]);
            d[u][0] += d[v][1];
        }
    }
}

void solve() {
    for (int i=1; i<=n; ++i) {
        cin >> c[i];
        for (int j=0; j<c[i]; ++j) cin >> g[i][j];
    }
    dfs();
    cout << max(min(d[1][0], d[1][1]), 1) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n && n) solve();
    return 0;
}