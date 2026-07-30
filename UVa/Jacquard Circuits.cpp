/**
 * UVa1059/LA2395
 * 提花织物电路板
 * World Finals >> 2007 - Tokyo
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 1002
long long x[N], y[N], m; bool f[N]; int n, kase = 0;

bool collinear(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3) {
    return (x2 - x1) * (y3 - y2) == (x3 - x2) * (y2 - y1);
}

void solve() {
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i], f[i] = true;
    for (int i=0; i<n; ++i) {
        int j = i ? i-1 : n-1, k = i+1==n ? 0 : i+1;
        if (collinear(x[j], y[j], x[i], y[i], x[k], y[k])) f[i] = false;
    }
    long long g = 0, s = 0, t = 0; int k = 0;
    for (int i=0; i<n; ++i) if (f[i]) x[k] = x[i], y[k++] = y[i];
    for (int i=1; i<k; ++i) {
        long long px = x[i-1], py = y[i-1], g1 = abs(__gcd(x[i]-px, y[i]-py));
        g = __gcd(g, g1); t += g1; s += (x[i]-x[0])*(py-y[0]) - (px-x[0])*(y[i]-y[0]);
    }
    long long g1 = abs(__gcd(x[0]-x[k-1], y[0]-y[k-1])); g = __gcd(g, g1); t = (t + g1) / g; s = abs(s)/g/g;
    long long ans = (m*__int128_t(m+1)*(2*m+1)/6*s - m*__int128_t(m+1)/2*t) / 2 + m;
    cout << "Case " << ++kase << ": " << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m && (m || n)) solve();
    return 0;
}