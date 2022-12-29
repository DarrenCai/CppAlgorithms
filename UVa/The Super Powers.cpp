/**
 * UVa11752
 * 超级幂
 */

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define N 64
#define ULL unsigned long long
ULL a[67500], x = 0xffffffffffffffff; int n = 1; bool f[N] = {0};

ULL power(ULL x, int n) {
    if (n == 0) return 1;
    ULL r = power(x, n>>1);
    return n&1 ? r*r*x : r*r;
}

int main() {
    // freopen("ou.txt", "w", stdout);
    a[0] = 1;
    for (ULL y=2; y<65536; ++y) a[n++] = power(y, 4);
    for (int i=2; i<N; ++i) if (!f[i]) for (int j=i<<1; j<N; j+=i) f[j] = true;
    for (int i=4; i<N; ++i) if (f[i]) for (int j=i<<1; j<N; j+=i) f[j] = false;
    for (int i=6; i<N; ++i) if (f[i]) {
        ULL y = pow(x, 1./i);
        for (ULL j=2; j<=y; ++j) a[n++] = power(j, i);
        for (int j=i<<1; j<N; j+=i) f[j] = false;
    }
    sort(a, a+n);
    n = unique(a, a+n) - a;
    for (int i=0; i<n; ++i) cout << a[i] << endl;
    return 0;
}