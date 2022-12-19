/**
 * UVa10294
 * 项链和手镯
 */

#include <iostream>
using namespace std;

#define N 52
int n, t; long long p[N];

int gcd(int a, int b) {
    if (a > b) return gcd(b, a);
    if (a < 0) return gcd(-a, b);
    if (a == 0) return b;
    if (a & 1) {
        if (b & 1) return gcd(a, (b-a)>>1);
        return gcd(a, b >> 1);
    } else {
        if (b & 1) return gcd(a >> 1, b);
        return gcd(a >> 1, b >> 1) << 1;
    }
}

void solve() {
    long long a = 0;
    for (int i=1; i<=n; ++i) p[i] = t*p[i-1], a += p[gcd(i, n)];
    int h = (n+1)>>1; long long b = n&1 ? n*p[h] : h * (p[h+1] + p[h]);
    cout << a/n << ' ' << (a + b) / n / 2 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    p[0] = 1;
    while (cin >> n >> t) solve();
    return 0;
}