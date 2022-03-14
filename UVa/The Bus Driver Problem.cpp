/**
 * UVa11389
 * 巴士司机问题
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 110
short n, r; int a[N], b[N], d;

int solve() {
    for (short i=0; i<n; ++i) cin >> a[i];
    for (short i=0; i<n; ++i) cin >> b[i];
    sort(a, a+n); sort(b, b+n);
    int ans = 0;
    for (short i=0, k=n-1; i<n; ++i) {
        int v = a[i] + b[k-i];
        if (v > d) ans += v-d;
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n>>d>>r && n) cout << r * solve() << endl;
    return 0;
}