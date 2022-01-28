/**
 * UVa11300
 * 分⾦币
 */

#include <iostream>
using namespace std;

#define N 1000200
long long a[N]; int n;

long long quick_select(int low, int high, int k) {
    while (true) {
        long long b = a[low]; int l = low+1, r = high;
        while (l <= r) {
            while (l<=r && a[l]<b) ++l;
            while (l<=r && a[r]>=b) --r;
            if (l<=r && a[l]>=b && a[r]<b) {
                long long t = a[l]; a[l++] = a[r]; a[r--] = t;
            }
        }
        a[low] = a[r]; a[r] = b;
        if (r == k) return a[r];
        r > k ? high = r-1 : low = r+1;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin >> n) {
        long long s = 0, ans = a[0] = 0;
        for (int i=1; i<=n; ++i) cin >> a[i], s += a[i];
        if (n>0) s /= n;
        for (int i=1; i<n; ++i) a[i] += a[i-1] - s;
        if (n>0) s = quick_select(0, n-1, n>>1);
        for (int i=0; i<n; ++i) ans += abs(s-a[i]);
        cout << ans << endl;
    }
    return 0;
}