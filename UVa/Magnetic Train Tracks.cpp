/**
 * UVa12123/LA4064
 * 铁轨
 * Dhaka 2007
 */

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define N 1205
int x[N], y[N], n, kase = 0; double a[N<<1], p2 = 2*M_PI, p_2 = M_PI_2 - 1e-9;

int obtuse(int p) {
    int m = n-1, ans = m*(m-1)/2;
    for (int i=0, j=0; i<n; ++i) if (i != p) a[j++] = atan2(y[i] - y[p], x[i] - x[p]);
    sort(a, a+m);
    for (int i=0; i<m; ++i) a[m+i] = a[i] + p2;
    for (int i=0, j=0; i<m; ++i) {
        while (a[j] <= a[i]+p_2) ++j;
        ans -= j-i-1;
    }
    return ans;
}

void solve() {
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i];
    int ans = n*(n-1)*(n-2)/6;
    for (int i=0; i<n; ++i) ans -= obtuse(i);
    cout << "Scenario " << ++kase << ':' << endl << "There are " << ans << " sites for making valid tracks" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n && n) solve();
    return 0;
}