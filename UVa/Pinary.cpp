/**
 * UVa1350/LA3357
 * Pinary数
 * Seoul 2005
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define K 90000000
int a[40], s[40], n;

void print(int n, int k) {
    for (int i=2, x=a[n]; i<n; x-=a[n-i++]) if (k > x-a[n-i]) {
        cout << 1;
        for (int j=1; j<i; ++j) cout << 0;
        return print(n-i, k+a[n-i]-x);
    }
    cout << 1;
    while (--n) cout << 0;
}

void solve() {
    int k; cin >> k;
    int m = lower_bound(s+1, s+n, k) - s;
    print(m, k-s[m-1]);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    s[1] = a[1] = a[n=2] = 1; s[0] = 0; s[2] = 2;
    while(s[n] < K) a[n+1] = a[n] + a[n-1], s[n+1] = s[n] + a[n+1], ++n;
    int t; cin >> t;
    while (t--) solve(), cout << endl;
    return 0;
}