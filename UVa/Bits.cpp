/**
 * UVa11645
 * 连续的比特
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 64
int kase = 0; long long n; unsigned long long p[N]; __uint128_t f[N];

void print(__uint128_t v) {
    if (v > 9) print(v / 10);
    cout << int(v % 10);
}

void solve() {
    int m = upper_bound(p+1, p+N, n) - p;
    __uint128_t ans = f[m-1];
    n ^= p[m-1];
    for (int i=m-1; i>0; --i) if (n&p[i-1]) {
        ans += f[i-1];
        n ^= p[i-1];
        if (m == i+1) ans += n+1;
        m = i;
    }
    cout << "Case " << ++kase << ": ";
    print(ans);
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    f[0] = f[1] = 0; p[0] = 1; p[1] = 2;
    for (int i=2; i<N; ++i) p[i] = p[i-1]<<1, f[i] = (f[i-1]<<1) + (1ll<<(i-2));
    while (cin>>n && n>=0) solve();
    return 0;
}