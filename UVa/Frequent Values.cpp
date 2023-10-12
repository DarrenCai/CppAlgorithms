/**
 * UVa11235
 * 频繁出现的数值
 */

#include <iostream>
using namespace std;

#define N 100010
int a[N], d[N][16], x[N], y[N], n, q;

int query(int l, int r) {
    if (l == r) return 1;
    int k = 0, ans;
    while (1<<k+1 <= r-l+1) ++k;
    ans = max(d[l][k], d[r-(1<<k)+1][k]);
    int p = l + (1<<k);
    if (p<=r && a[p]==a[p-1]) ans = max(ans, min(r+1, y[p]+1) - max(x[p], l));
    return ans;
}

void solve() {
    cin >> q;
    for (int i=1; i<=n; ++i) cin >> a[i], d[i][0] = 1, x[i] = y[i] = i;
    for (int i=n-1; i>0; --i) if (a[i] == a[i+1]) y[i] = y[i+1];
    for (int i=2; i<=n; ++i) if (a[i] == a[i-1]) x[i] = x[i-1];
    for (int j=1; (1<<j) <= n; ++j) for (int i=1; i+(1<<j)-1 <= n; ++i) {
        int p = i+(1<<j-1);
        d[i][j] = max(d[i][j-1], d[p][j-1]);
        if (a[p] == a[p-1]) d[i][j] = max(d[i][j], min(i+(1<<j), y[p]+1) - max(x[p], i));
    }
    while (q--) {
        int l, r; cin >> l >> r;
        cout << query(l, r) << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n && n) solve();
    return 0;
}