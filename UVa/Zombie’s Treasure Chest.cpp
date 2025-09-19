/**
 * UVa12325/LA5703
 * 宝箱
 * Shanghai 2011
 */

#include <iostream>
using namespace std;

int gcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1; y = 0; return a;
    } else {
        int g = gcd(b, a%b, y, x);
        y -= a/b*x;
        return g;
    }
}

long long solve() {
    int n, s1, s2; long long v1, v2; cin >> n >> s1 >> v1 >> s2 >> v2;
    int x = min(s1, s2) - 1, y = min(n/s1, n/s2); long long ans = 0;
    if (x < y) {
        int a, b, g = gcd(s1, s2, a, b), i = s1/g, j = s2/g; long long k = v1*j - v2*i;
        for (y=n-x; y<=n; ++y) if (y%g == 0) {
            long long u = y/g*(long long)a, v = y/g*(long long)b, c1 = (u<0 ? j-1-u : -u)/j, c2 = (v<0 ? v+1-i : v)/i;
            if (c1 > c2) continue;
            ans = max(ans, v1*u + v2*v + k * (k > 0 ? c2 : c1));
        }
    } else if (s1 > s2) for (int i=n/s1; i>=0; --i) ans = max(ans, v1*i + (n-i*s1)/s2*v2);
    else for (int i=n/s2; i>=0; --i) ans = max(ans, v2*i + (n-i*s2)/s1*v1);
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) cout << "Case #" << k << ": " << solve() << endl;
    return 0;
}