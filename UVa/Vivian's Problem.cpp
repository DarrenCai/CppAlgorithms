/**
 * UVa1323/LA2955
 * Vivian的难题
 * Guangzhou 2003
 * 知识点：梅森素数（Mersenne prime）https://en.wikipedia.org/wiki/Mersenne_prime
 */

#include <iostream>
using namespace std;

#define M 8
#define N 256
int p[] = {2, 3, 5, 7, 13, 17, 19, 31}, msp[] = {3, 7, 31, 127, 8191, 131071, 524287, 2147483647}, d[N], w[N] = {0}, k;

void solve() {
    for (int i=1; i<N; ++i) d[i] = 0;
    for (int i=1; i<=k; ++i) {
        int x, v = 0; cin >> x;
        for (int i=0; i<M; ++i) if (x%msp[i] == 0) x /= msp[i], v |= 1<<i;
        if (x == 1) for (int j=0; j<N; ++j) if (d[j] && (j&v)==0) d[j|v] = 1;
    }
    int ans = 0; for (int i=1; i<N; ++i) if (d[i]) ans = max(ans, w[i]);
    ans ? cout << ans << endl : cout << "NO" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    d[0] = 1;
    for (int i=0; i<M; ++i) w[1<<i] = p[i];
    for (int i=3; i<N; ++i) w[i] = w[i&(-i)] + w[i&(i-1)];
    while (cin >> k) solve();
    return 0;
}