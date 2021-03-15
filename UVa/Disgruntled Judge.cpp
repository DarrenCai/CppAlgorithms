/**
 * UVa12169
 * 不爽的裁判
 */

#include <iostream>
using namespace std;

#define T 111
short x[T<<1], t; const int M = 10001;

void solve() {
    for (short a=0; a<M; ++a) for (short b=0; b<M; ++b) {
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