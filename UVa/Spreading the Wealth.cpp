/**
 * UVa11300
 * 分⾦币
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 1000200
long long a[N]; int n;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin >> n) {
        long long s = 0, ans = a[0] = 0;
        for (int i=1; i<=n; ++i) cin >> a[i], s += a[i];
        if (n>0) s /= n;
        for (int i=1; i<n; ++i) a[i] += a[i-1] - s;
        sort(a, a+n);
        s = a[n>>1];
        for (int i=0; i<n; ++i) ans += abs(s-a[i]);
        cout << ans << endl;
    }
    return 0;
}