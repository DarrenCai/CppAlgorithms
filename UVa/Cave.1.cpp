/**
 * UVa1442/LA4621
 * 洞穴
 * CERC 2009
 */

#include <iostream>
using namespace std;

#define N 1000100
int p[N], s[N], l[N], r[N];

int solve() {
    int ans = 0, n; cin >> n;
    for (int i=0; i<n; ++i) cin >> p[i];
    for (int i=0; i<n; ++i) cin >> s[i];
    l[0] = s[0]; r[n-1] = s[n-1];
    for (int i=1; i<n; ++i) {
        l[i] = min(s[i], max(l[i-1], p[i-1]));
        r[n-1-i] = min(s[n-1-i], max(r[n-i], p[n-i]));
    }
    for (int i=0; i<n; ++i) ans += max(min(l[i], r[i]), p[i]) - p[i];
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int k; cin>>k;
    while (k--) cout << solve() << endl;
    return 0;
}