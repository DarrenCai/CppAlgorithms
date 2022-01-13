/**
 * UVa1669
 * 交换房子
 */

#include <iostream>
#include <vector>
using namespace std;

#define N 100100
int u[N], v[N], n; long long w[N], ans; vector<int> g[N];

int dfs(int i, int p = -1) {
    int a = p>0 && (v[i]==u[p] || v[i]==v[p]) ? u[i] : v[i], c = 0;
    for (int j=g[a].size()-1, k; j>=0; --j) if ((k=g[a][j]) != i && k != p) c += 1 + dfs(k, i);
    ans += w[i]*min(c+1, n-c-1)<<1;
    return c;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) {
        cin >> n;
        for (int i=1; i<=n; ++i) g[i].clear();
        for (int i=1; i<n; ++i) cin >> u[i] >> v[i] >> w[i], g[u[i]].push_back(i), g[v[i]].push_back(i);
        ans = 0; dfs(1);
        cout << "Case #" << kase << ": " << ans << endl;
    }
    return 0;
}