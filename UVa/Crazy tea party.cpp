/**
 * UVa1315/LA2756
 * SEERC 2003
 */

#include <iostream>
using namespace std;

void solve() {
    int n, h; cin >> n;
    h = n>>1; n -= h;
    cout << n*(n-1)/2 + h*(h-1)/2 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}