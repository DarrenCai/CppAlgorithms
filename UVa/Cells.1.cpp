/**
 * UVa1357/LA3486
 * Hangzhou 2005
 */

#include <iostream>
using namespace std;

#define M 300050
#define N 20000100
int g[M][102], c[M], pre[N], post[N], s[N<<1], m, n, t, clk; bool vis[M];

void solve() {
    cin >> n; t = clk = vis[0] = false;
    for (int i=0; i<n; i++) {
        cin >> c[i]; vis[i] = false;
        for (int j=0; j<c[i]; ++j) g[i][j] = ++t;
    }
    int p = 1; s[0] = 0;
    while (p) {
        int u = s[--p];
        if (u >= n) {
            pre[u] = post[u] = ++clk;
        } else if (!vis[u]) {
            pre[u] = ++clk; vis[s[p++] = u] = true;
            for (int i=0; i<c[u]; ++i) s[p++] = g[u][i];
        } else post[u] = ++clk;
    }
    cin >> m;
    while (m--) {
        int a, b; cin >> a >> b;
        cout << (pre[a]<pre[b] && post[b]<post[a] ? "Yes" : "No") << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) {
        if (k > 1) cout << endl;
        cout << "Case " << k << ':' << endl;
        solve();
    }
    return 0;
}