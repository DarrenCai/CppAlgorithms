/**
 * UVa1664/LA6070
 * 占领新区域
 * Changchun 2012
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 200010
int a[N], b[N], c[N], e[N], f[N], n; long long d[N], w[N];

bool cmp(int i, int j) {
    return w[i] > w[j];
}

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

void solve() {
    for (int i=1; i<=n; ++i) {
        c[i] = 1; d[i] = 0; f[i] = i;
        if (i < n) cin >> a[i] >> b[i] >> w[i], e[i] = i;
    }
    sort(e+1, e+n, cmp);
    long long ans = 0;
    for (int i=1; i<n; ++i) {
        int u = find(a[e[i]]), v = find(b[e[i]]);
        ans = d[v] = max(c[u] * w[e[i]] + d[v], c[v] * w[e[i]] + d[u]); c[v] += c[u]; f[u] = v;
    }
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n) solve();
    return 0;
}