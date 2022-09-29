/**
 * UVa12080/LA3412
 * 佩斯基英雄
 * NWERC 2005
 * 雅礼中学女大佬陈丹琦的解法
 */

#include <iostream>
using namespace std;

#define N 50010
#define M 505
int t[N][3], f[N], g[N], c[N], n, m; bool trap[N];

bool dfs(int u, int fa = 0) {
    if (trap[u]) {
        f[u] = g[u] = 0;
    } else if (c[u] == 1 && u > 1) {
        f[u] = 1; g[u] = 0;
    } else if (c[u] == 2 || u == 1) {
        int s = u==1 ? t[u][0] : t[u][0]+t[u][1]-fa;
        if (dfs(s, u)) trap[u] = true;
        f[u] = f[s]; g[u] = g[s];
    } else {
        int l = t[u][0]!=fa ? t[u][0] : t[u][1], r = t[u][0]+t[u][1]+t[u][2]-fa-l;
        if (dfs(l, u)) trap[u] = true;
        if (dfs(r, u)) trap[u] = true;
        g[u] = trap[l] && trap[r] ? N : min(g[l] + g[r], min(g[l] + f[r], g[r] + f[l]));
        f[u] = min(f[l]+f[r], g[u]+1);
    }
    return trap[u];
}

int solve() {
    for (int u=1; u<=n; ++u) {
        cin >> c[u]; trap[u] = false;
        for (int i=0; i<c[u]; ++i) cin >> t[u][i];
    }
    while (m--) {
        int u; cin >> u; trap[u] = true;
    }
    dfs(1);
    return f[1];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n>>m && n) cout << solve() << endl;
    return 0;
}