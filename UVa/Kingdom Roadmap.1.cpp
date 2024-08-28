/**
 * UVa1670/LA5920
 * 王国的道路图
 * NEERC 2011
 */

#include <iostream>
#include <vector>
using namespace std;

#define N 100100
int q[N], n, c; vector<int> g[N];

void dfs(int u, int p = -1) {
    if (g[u].size() == 1) q[c++] = u;
    for (int i=g[u].size()-1, v; i>=0; --i) if ((v = g[u][i]) != p) dfs(v, u);
}

void solve() {
    c = 0;
    for (int i=1; i<=n; ++i) g[i].clear();
    for (int i=1, u, v; i<n; ++i) cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
    for (int i=1; i<=n; ++i) if (g[i].size() > 1) {
        dfs(i); break;
    }
    cout << (c+1)/2 << endl;
    for (int i=0, m=c>>1; i<m; ++i) cout << q[i] << ' ' << q[i+m] << endl;
    if (c&1) cout << q[0] << ' ' << q[c-1] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n) solve();
    return 0;
}