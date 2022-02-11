/**
 * UVa11078
 * 开放式学分制
 */

#include <iostream>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    short t; cin >> t;
    while (t--) {
        int n, mx, x, ans=0x80000000; cin >> n >> mx;
        while (--n) {
            cin >> x;
            ans = max(ans, mx-x);
            mx = max(mx, x);
        }
        cout << ans << endl;
    }
    return 0;
}