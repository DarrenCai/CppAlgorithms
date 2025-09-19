/**
 * UVa11059
 * 最大乘积
 */

#include <iostream>
using namespace std;

#define N 18
int a[N], n, kase = 0;

void solve() {
    for (int i=0; i<n; ++i) cin >> a[i];
    long long ans = 0;
    for (int i=0; i<n; ++i) {
        long long v = 1;
        for (int j=i; j<n; ++j) ans = max(ans, v *= a[j]);
    }
    cout << "Case #" << ++kase << ": The maximum product is " << ans << "." << endl << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) solve();
    return 0;
}