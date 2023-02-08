/**
 * UVa1485/LA5092
 * 排列统计
 * Harbin 2010
 */

#include <iostream>
using namespace std;

#define M 1000000007
#define N 1002
int f[N][N>>1], n, k;

int solve() {
    return k >= n ? 0 : ((k<<1) < n ? f[n][k] : f[n][n-1-k]);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (long long n=1; n<N; ++n) {
        f[n][0] = 1;
        for (long long k=1, m=(n-1)>>1; k<=m; ++k)
            f[n][k] = ((f[n-1][(k<<1) < n-1 ? k : k-1])*(k+1) + f[n-1][k-1]*(n-k)) % M;
    }
    while (cin >> n >> k) cout << solve() << endl;
    return 0;
}