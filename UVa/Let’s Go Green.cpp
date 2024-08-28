/**
 * UVa1668/LA6039
 * 绿色行动
 * Jakarta 2012
 */

#include <iostream>
using namespace std;

#define N 100010
int u[N], v[N], w[N], x[N], s[N], f[N], n;

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

int solve() {
    cin >> n;
    for (int i=1; i<=n; ++i) x[i] = s[i] = 0, f[i] = i;
    for (int i=1; i<n; ++i) {
        cin >> u[i] >> v[i] >> w[i]; s[u[i]] += w[i]; s[v[i]] += w[i];
        x[u[i]] = max(x[u[i]], w[i]); x[v[i]] = max(x[v[i]], w[i]);
    }
    for (int i=1; i<=n; ++i) s[i] = max(x[i], (s[i]+1) >> 1);
    int cc = 0;
    for (int i=1; i<n; ++i) {
        int x = find(u[i]), y = find(v[i]); f[x] = y; cc = s[y] += s[x] - w[i];
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) cout << "Case #" << k << ": " << solve() << endl;
    return 0;
}