/**
 * UVa11525
 * 排列
 */

#include <iostream>
using namespace std;

int c[1<<17], k, s;

int query(int o, int l, int r) {
    int ans = l;
    if (l < r) {
        int m = (l+r) >> 1, lc = o << 1, rc = lc + 1;
        if (c[o] == r-l+1) c[lc] = m-l+1, c[rc] = r-m;
        ans = c[lc] < s ? (s -= c[lc], query(rc, m+1, r)) : query(lc, l, m);
        c[o] = c[lc] + c[rc];
    } else c[o] = 0;
    return ans;
}

void solve() {
    cin >> k; c[1] = k;
    for (int i=1; i<=k; ++i) {
        cin >> s; ++s;
        cout << query(1, 1, k);
        i < k ? cout << ' ' : cout << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}