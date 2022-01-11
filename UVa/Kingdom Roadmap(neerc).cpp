/**
 * UVa1670
 * 王国的道路图
 */

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define N 100100
int a[N], n, c; vector<int> g[N];

void dfs(int u, int p = -1) {
    if (g[u].size() == 1) a[c++] = u;
    for (int i=g[u].size()-1; i>=0; --i) {
        int v = g[u][i];
        if (v != p) dfs(v, u);
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) {
        int u, v; c = 0;
        for (int i=1; i<=n; ++i) g[i].clear();
        for (int i=1; i<n; ++i) cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
        if (n > 2) {
            for (int i=1; i<=n; ++i) if (g[i].size() > 1) {
                dfs(i); break;
            }
            cout << (c+1)/2 << endl;
            for (int m=c/2, i=0; i<m; ++i) cout << a[i] << ' ' << a[i+m] << endl;
            if (c&1) cout << a[0] << ' ' << a[c-1] << endl;
        } else cout << 1 << endl << "1 2" << endl;
    }
    return 0;
}