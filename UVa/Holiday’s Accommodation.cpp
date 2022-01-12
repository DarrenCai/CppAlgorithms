/**
 * UVa1669
 * 交换房子
 */

#include <iostream>
#include <vector>
using namespace std;

#define N 100100
int u[N], v[N], cu[N], cv[N], n; long long w[N]; vector<int> g[N];

int dfs(int i, int p = -1) {
    cu[i] = cv[i] = 0;
    bool isU = p>0 && (v[i]==u[p] || v[i]==v[p]);
    int a = isU ? u[i] : v[i], &ref = isU ? cu[i] : cv[i];
    for (int j=g[a].size()-1, k; j>=0; --j) if ((k=g[a][j]) != i && k != p) ref += 1 + dfs(k, i);
    return ref;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) {
        cin >> n;
        for (int i=1; i<=n; ++i) g[i].clear();
        for (int i=1; i<n; ++i) cin >> u[i] >> v[i] >> w[i], g[u[i]].push_back(i), g[v[i]].push_back(i);
        dfs(1);
        long long ans = 0;
        for (int i=1; i<n; ++i) {
            cu[i] == 0 ? (++cv[i], cu[i]=n-cv[i]) : (++cu[i], cv[i]=n-cu[i]);
            ans += w[i]*(min(cu[i], cv[i]))<<1;
        }
        cout << "Case #" << kase << ": " << ans << endl;
    }
    return 0;
}