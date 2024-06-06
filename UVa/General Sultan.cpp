/**
 * UVa11604
 * 有歧义的编码
 */

#include <iostream>
#include <cstring>
using namespace std;

#define L 22
#define N 101
int g[N*L][N*L], c[N*L], e[N], t[N], m, n, kase = 0; char s[N][L], tmp[L]; bool vis[N*L];

int common(int i, int h, int j) {
    int k = 0;
    while (h < e[i]) {
        if (s[i][h] != s[j][k]) return k;
        ++h; ++k;
    }
    return k;
}

bool dfs(int u = 0) {
    if (u == m) return true;
    vis[u] = true;
    for (int i=0, v; i<c[u]; ++i) if (!vis[v = g[u][i]] && dfs(v)) return true;
    return false;
}

void solve() {
    memset(c, 0, sizeof(c)); memset(vis, 0, sizeof(vis));
    for (int i=0; i<n; ++i) cin >> tmp >> s[i], e[i] = strlen(s[i]), g[0][c[0]++] = t[i] = i<1 ? 1 : t[i-1] + e[i-1];
    m = t[n-1] + e[n-1];
    for (int i=0; i<n; ++i) for (int j=0; j<e[i]; ++j) for (int k=0; k<n; ++k) {
        if (i==k && j==0) continue;
        int cc = common(i, j, k), u = t[i]+j;
        if (cc == e[k] && cc+j == e[i]) g[u][c[u]++] = m;
        else if (cc < e[k] && cc+j == e[i]) g[u][c[u]++] = t[k] + cc;
        else if (cc == e[k] && cc+j < e[i]) g[u][c[u]++] = u + cc;
    }
    cout << "Case #" << ++kase << (dfs() ? ": Ambiguous." : ": Not ambiguous.") << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n && n) solve();
    return 0;
}