/**
 * UVa1335
 * 长城守卫
 */

#include <iostream>
using namespace std;

#define N 1000100
int r[N], n;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n && n) {
        long long s = 0; int m = n>>1;
        for (int i=0; i<n; ++i) cin >> r[i], s += r[i];
        int ans = m<1 ? r[0] : max(int((s+m-1)/m), r[n-1]+r[0]);
        for (int i=1; i<n; ++i) ans = max(ans, r[i-1]+r[i]);
        cout << ans << endl;
    }
    return 0;
}