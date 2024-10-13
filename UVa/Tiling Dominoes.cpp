/**
 * UVa11270
 * 铺放骨牌
 */

#include <iostream>
#include <cstring>
using namespace std;

long long d[2][1024]; int p[1<<20][2], m, n, c;

void dfs(int i, int v) {
    if (i == n) {
        d[0][v] = 1;
        return;
    }
    dfs(i+1, v | 1<<i);
    if (i+1 < n) dfs(i+2, v);
}

void dfs(int i, int u, int v) {
    if (i == n) {
        p[c][0] = u; p[c++][1] = v;
        return;
    }
    if (u&(1<<i)) return dfs(i+1, u, v);
    dfs(i+1, u, v | 1<<i);
    if (++i < n && ~u&(1<<i)) dfs(i+1, u, v);
}

void solve() {
    if (m < n) m += n, n = m - n, m = m - n;
    memset(d[0], 0, sizeof(d[0]));
    dfs(0, 0);
    for (int i=c=0, j=1<<n; i<j; ++i) dfs(0, i, 0);
    for (int i=1; i<m; ++i) {
        memset(d[i&1], 0, sizeof(d[0]));
        for (int j=0; j<c; ++j) d[i&1][p[j][1]] += d[~i&1][p[j][0]];
    }
    cout << d[~m&1][0] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) solve();
    return 0;
}