/**
 * UVa1335
 * 长城守卫
 */

#include <iostream>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int n, r0;
    while (cin>>n && n && cin>>r0) {
        long long s = r0; int m = n>>1, p = r0, r, ans = r0;
        for (int i=1; i<n; ++i) cin >> r, s += r, ans = max(ans, r+p), p = r;
        if (n > 1) ans = max(ans, max(int((s+m-1)/m), r0+r));
        cout << ans << endl;
    }
    return 0;
}