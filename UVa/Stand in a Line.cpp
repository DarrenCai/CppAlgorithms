/**
 * UVa11174
 * 村民排队
 */

#include <iostream>
#include <vector>
using namespace std;

#define N 40001
#define M 1000000007
int d[N], f[N], r[N], m, n, ans; vector<int> g[N];

int dfs(int u = 0) {
    f[u] = 1;
    for (int i=g[u].size()-1; i>=0; --i) f[u] += dfs(g[u][i]);
    return f[u];
}

void solve() {
    cin >> n >> m;
    for (int i=0; i<=n; ++i) f[i] = 0, g[i].clear();
    for (int i=0, u, v; i<m; ++i) cin >> u >> v, f[u] = v;
    for (int i=1; i<=n; ++i) g[f[i]].push_back(i);
    dfs();
    long long ans = d[n];
    for (int i=1; i<=n; ++i) if (f[i] > 1) ans = ans * r[f[i]] % M;
    cout << ans << endl;
}

int gcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1; y = 0; return a;
    } else {
        int g = gcd(b, a%b, y, x);
        y -= a/b*x;
        return g;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    d[0] = 1; for (long long i=1; i<N; ++i) d[i] = i * d[i-1] % M;
    for (int i=2; i<N; ++i) gcd(i, M, r[i], r[0]), r[i] = (M + r[i] % M) % M;
    short t; cin >> t;
    while (t--) solve();
    return 0;
}