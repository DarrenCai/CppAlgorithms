/**
 * UVa12080/LA3412
 * 佩斯基英雄
 * NWERC 2005
 */

#include <iostream>
using namespace std;

#define N 50010
#define M 505
int d[N][3], g[N][3], c[N], n, m; bool trap[N];

void dfs(int u, int fa = 0) {
    if (trap[u]) {
        d[u][0] = 0; d[u][1] = d[u][2] = N;
    } else if (c[u] == 1 && u > 1) {
        d[u][0] = 1; d[u][1] = d[u][2] = 0;
    } else if (c[u] == 2 || u == 1) {
        int s = u==1 ? g[u][0] : g[u][0]+g[u][1]-fa;
        dfs(s, u);
        d[u][0] = d[s][0]; d[u][1] = d[s][1]; d[u][2] = d[s][2];
    } else {
        int l = g[u][0]!=fa ? g[u][0] : g[u][1], r = g[u][0]+g[u][1]+g[u][2]-fa-l;
        dfs(l, u); dfs(r, u);
        d[u][2] = d[l][2] + d[r][2];
        d[u][1] = min(d[l][2] + min(d[r][0], d[r][1]), d[r][2] + min(d[l][0], d[l][1]));
        d[u][0] = min(d[l][0] + d[r][0], 1 + d[u][1]);
    }
}

int solve() {
    for (int u=1; u<=n; ++u) {
        cin >> c[u]; trap[u] = false;
        for (int i=0; i<c[u]; ++i) cin >> g[u][i];
    }
    while (m--) {
        int u; cin >> u; trap[u] = true;
    }
    dfs(1);
    return d[1][0];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n>>m && n) cout << solve() << endl;
    return 0;
}