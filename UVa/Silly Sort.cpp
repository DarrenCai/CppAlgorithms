/**
 * UVa1016/LA2481
 * 傻傻的排序
 * World Finals >> 2002 - Honolulu
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 1005
int a[N], b[N], p[N], q[N], n, kase = 0;

void solve() {
    for (int i=0; i<n; ++i) cin >> a[i], p[b[i] = a[i]] = i;
    sort(a, a+n);
    for (int i=0; i<n; ++i) q[a[i]] = i;
    int ans = 0;
    for (int t=n-1; t>0; --t) if (a[t] != b[t]) {
        int c = 1, m = a[t], s = m;
        for (int x = p[a[t]], y = t, z; x != y; b[y] = b[x], y = q[b[x] = z]) ++c, z = b[y], s += z, m = min(m, z);
        ans += min(s + (c-2)*m, (c+1)*a[0] + s + m);
    }
    cout << "Case " << ++kase << ": " << ans << endl << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) solve();
    return 0;
}
