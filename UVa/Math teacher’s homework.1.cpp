/**
 * UVa1489/LA5101
 * 数学老师的作业
 * Fuzhou 2010
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 1000000003
#define N 51
long long f[N][N]; int a[N], n, x;

int solve() {
    long long ans = 0;
    for (int i=1; i<=n; ++i) cin >> a[i];
    for (int i=30; i>=0; --i) {
        memset(f, 0, sizeof(f)); f[0][0] = 1;
        int b = 1<<i, t = 0;
        for (int j=1; j<=n; ++j) {
            if (a[j] & b) {
                for (int k=0; k<=t; ++k) f[j][k] = f[j-1][k] * (1 + (a[j]&~b)) % M;
                for (int k = ++t; k>1; --k) f[j][k] = (f[j][k] + b * f[j-1][k-1]) % M;
                f[j][1] = (f[j][1] + f[j-1][0]) % M;
                a[j] ^= b;
            } else for (int k=0; k<=t; ++k) f[j][k] = f[j-1][k] * (1 + a[j]) % M;
        }
        for (int j=1; j<=t; ++j) if (((t-j) & 1) == (x>>i & 1)) ans += f[n][j];
        if ((x>>i & 1) != (t&1)) return ans % M;
    }
    return (ans + 1) % M;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n>>x && n) cout << solve() << endl;
    return 0;
}