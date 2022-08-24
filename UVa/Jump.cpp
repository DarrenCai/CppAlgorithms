/**
 * UVa1452/LA4727
 * 跳跃
 * Seoul 2009
 */

#include <iostream>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    int a = 1, b = (k-1)%2+1, c = (k-1)%3+1;
    for (int i=2; i<=n; ++i) a = (a+k-1)%i + 1;
    for (int i=3; i<=n; ++i) b = (b+k-1)%i + 1;
    for (int i=4; i<=n; ++i) c = (c+k-1)%i + 1;
    cout << c << ' ' << b << ' ' << a << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}