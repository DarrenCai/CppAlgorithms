/**
 * UVa10534
 * 波浪子序列
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 10050
int a[N], g[N], l[N], n;

int solve() {
    for (int i=1; i<=n; ++i) cin >> a[i];
    g[1] = a[1];
    for (int i=2, t=2; i<n; ++i) {
        int k = lower_bound(g+1, g+t, a[i]) - g;
        g[l[i] = k==t ? t++ : k] = a[i];
    }
    int ans = 1; g[1] = a[n];
    for (int i=n-1, t=2; i>1; --i) {
        int k = lower_bound(g+1, g+t, a[i]) - g;
        g[k==t ? t++ : k] = a[i];
        ans = max(ans, (min(l[i], k)<<1) - 1);
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n) cout << solve() << endl;
    return 0;
}