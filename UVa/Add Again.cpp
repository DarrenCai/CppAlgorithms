/**
 * UVa11076
 * 排列之和
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 13
int a[N], b[N], c[N], m, n; long long p[N], q[N];

void solve() {
    for (int i=0; i<n; ++i) cin >> a[i];
    sort(a, a+n);
    for (int i=0; i<n; ++i) b[i] = a[i];
    m = unique(b, b+n) - b;
    long long ans = 0, x = 1;
    for (int i=0; i<m; ++i) c[i] = upper_bound(a, a+n, b[i]) - lower_bound(a, a+n, b[i]), x *= p[c[i]];
    for (int i=0; i<m; ++i) ans += p[n-1]*c[i]/x*b[i];
    cout << ans*q[n] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    p[0] = 1;
    for (int i=1; i<N; ++i) p[i] = p[i-1]*i;
    q[1] = 1;
    for(int i=2; i<N; ++i) q[i] = q[i-1]*10 + 1;
    while (cin>>n && n) solve();
    return 0;
}