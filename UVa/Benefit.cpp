/**
 * UVa11889
 * 最小公倍数
 */

#include <iostream>
using namespace std;

long long gcd(long long a, long long b) {
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
    long long a, c; cin >> a >> c;
    if (c % a) {
        cout << "NO SOLUTION" << endl;
        return;
    }
    long long g = gcd(c/a, a), b = g*c/a;
    if (g > 1 && (a /= g) > 1) {
        for (long long i=2; i<g; ++i) if (g%i == 0) {
            while (g%i == 0) g /= i;
            while (a%i == 0) b *= i, a /= i;
        }
        if (g > 1) while (a%g == 0) b *= g, a /= g;
    }
    cout << b << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}