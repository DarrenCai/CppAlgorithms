/**
 * UVa10125
 * 和集
 * Waterloo local 2001.06.02
 */

#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

#define INF -2000000000
#define N 1020
int a[N], n;

void solve() {
    int ans = INF;
    for (int i=0; i<n; ++i) cin >> a[i];
    sort(a, a+n);
    set<int> s0, s1;
    for (int i=0; i<n; ++i) {
        for (int j=i+1; j<n; ++j) if (s0.count(a[j]-a[i])) ans = max(ans, a[j]);
        for (int j=i+1; j<n; ++j) if (s0.count(a[i]-a[j])) ans = max(ans, a[i]);
        for (int j=0; j<i; ++j) s0.insert(a[j]+a[i]);
    }
    for (int i=n-1; i>=0; --i) {
        for (int j=0; j<i; ++j) if (s1.count(a[j]-a[i])) ans = max(ans, a[j]);
        for (int j=0; j<i; ++j) if (s1.count(a[i]-a[j])) ans = max(ans, a[i]);
        for (int j=i+1; j<n; ++j) s1.insert(a[j]+a[i]);
    }
    if (ans > INF) cout << ans << endl;
    else cout << "no solution" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) solve();
    return 0;
}