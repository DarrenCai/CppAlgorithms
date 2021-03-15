/**
 * UVa12169
 * 不爽的裁判
 */

#include <iostream>
using namespace std;

#define T 111
short x[T<<1], t; const int M = 10001;

int gcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1; y = 0; return a;
    } else {
        int g = gcd(b, a%b, y, x);
        y -= a/b*x;
        return g;
    }
}

void solve() {
    for (short a=0; a<M; ++a) {
        int b, y, g = gcd(a+1, M, b, y), c = x[3]-a*a%M*x[1]%M;
        if (c%g) continue;
        b = c/g*b%M;
        short i=0;
        while (++i <= t) {
            x[i<<1] = (a*x[(i<<1)-1]%M+b)%M;
            if (i<t && x[(i<<1)+1] != (a*x[i<<1]%M+b)%M) break;
        }
        if (i > t) return;
    }
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> t) {
        for (short i=1; i<=t; ++i) cin >> x[(i<<1)-1];
        solve();
        for (short i=1; i<=t; ++i) cout << x[i<<1] << endl;
    }
    return 0;
}