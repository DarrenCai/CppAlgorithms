/**
 * UVa1372/LA3610
 * 跳木棍
 * Asia Seoul 2006
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 5020
int x[N];

void solve() {
    int ans = 0, d = 0, n, k; cin >> n >> k;
    for (int i=0; i<n; ++i) cin >> x[i];
    sort(x, x+n);
    if (n>1) ans = max(ans, d = x[1] < x[0]+k);
    for (int i=2; i<n; ++i)
        ans = max(ans, d = x[i] <= x[i-1]+k ? (x[i] <= x[i-2]+k ? d+1 : 1) : 0);
    cout << ans+1 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    short t; cin >> t;
    while (t--) solve();
    return 0;
}