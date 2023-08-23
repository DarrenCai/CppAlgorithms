/**
 * UVa10655
 * n次方之和
 */

#include <iostream>
using namespace std;

long long p, q, n;

long long solve() {
    if (n == 0) return 2;
    if (n == 1) return p;
    long long a = 0, b = 1, c = -q, d = p, e = 1, f = 0, g = 0, h = 1, f1 = p, f2 = p*p - 2*q;
    if (n == 2) return f2;
    for (long long k=n-2; k>0; k>>=1) {
        if (k & 1) {
            long long i = e*a + f*c; f = e*b + f*d; e = i;
            i = g*a + h*c; h = g*b + h*d; g = i;
        }
        long long x = a, y = b, z = c, w = d;
        a = x*x + y*z; b = x*y + y*w; c = z*x + w*z; d = z*y + w*w;
    }
    return g*f1 + h*f2;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> p >> q >> n) cout << solve() << endl;
    return 0;
}