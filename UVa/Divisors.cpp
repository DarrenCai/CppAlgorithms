/**
 * UVa294
 * 约数
 */

#include <iostream>
#include <cmath>
using namespace std;

#define N 31624
#define C 3410
bool flag[N] = {false}; short prim[C], c=0;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (short i=2; i<178; ++i) for (short j=i*i; j<N; j+=i) flag[j] = true;
    for (short i=2; i<N; ++i) if (!flag[i]) prim[c++] = i;
    short t; cin >> t;
    while (t--) {
        int l, u, s, m=0; cin >> l >> u;
        for (int i=l; i<=u; ++i) {
            int n = 1, v = sqrt(i+.5), ii=i;
            for (int j=0; j<c && prim[j] <= v; ++j) if (ii%prim[j] == 0) {
                short a = 1; while (ii%prim[j] == 0) ii /= prim[j], ++a;
                n *= a;
            }
            if (ii > 1) n <<= 1;
            if (n > m) s = i, m = n;
        }
        cout << "Between " << l << " and " << u << ", " << s << " has a maximum of " << m << " divisors." << endl;
    }
    return 0;
}