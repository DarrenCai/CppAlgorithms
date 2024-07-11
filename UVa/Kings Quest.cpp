/**
 * UVa1327/LA2966
 * 国王的要求
 * NEERC 2003
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 4020
int g[N][N>>1], c[N], s[N], sn[N], pre[N], clk, cc, n, p = 0;

int dfs(int u) {
    int low = pre[u] = ++clk; s[p++] = u;
    for (int i=0, v; i<c[u]; ++i) if (!pre[v = g[u][i]]) {
        low = min(low, dfs(v));
    } else if (!sn[v]) low = min(low, pre[v]);
    if (low == pre[u]) {
        ++cc;
        while (true) {
            sn[s[--p]] = cc;
            if (s[p] == u) break;
        }
    }
    return low;
}

void solve () {
    memset(pre, clk = 0, sizeof(pre)); memset(sn, cc = p = 0, sizeof(sn));
    for (int i=1; i<=n; ++i) {
        cin >> c[i]; c[i+n] = 1;
        for (int j=0; j<c[i]; ++j) cin >> g[i][j], g[i][j] += n;
    }
    for (int i=1, x; i<=n; ++i) cin >> x, g[x+n][0] = i;
    for (int u=1; u<=n; ++u) if (!pre[u]) dfs(u);
    for (int i=1, k; i<=n; ++i) {
        for (int j=k=0, x; j<c[i]; ++j) if (sn[i] == sn[x = g[i][j]]) s[k++] = x-n;
        cout << k;
        while (k--) cout << ' ' << s[k];
        cout << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n) solve();
    return 0;
}