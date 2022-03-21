/**
 * UVa10718
 */

#include <iostream>
using namespace std;

#define ull unsigned long long

ull solve(ull n, ull l, ull u) {
    if (l == u) return l;
    ull x = 1, m = 0, n1 = ~n;
    while (x < u) x <<= 1;
    if (x > u) x >>= 1;
    for (ull y=x; y>0; y>>=1) if ((n1&y) && (m|y)<=u) m |= y;
    if (m >= l) return m;
    for (ull y=1; y<=l; y<<=1) x = y;
    return x + solve(n|x, l-x, u-x);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ull n, l, u;
    while (cin>>n>>l>>u) {
        cout << solve(n, l, u) << endl;
    }
    return 0;
}
