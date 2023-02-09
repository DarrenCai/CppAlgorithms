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
long long f[N][32][2], a[N], c[N][32], n, x;

int solve() {
    memset(f, 0, sizeof(f));
    for (int i=0; i<n; ++i) cin >> a[i], ++a[i];
    for (int i=0; i<32; ++i) {
        if (a[0]>>i & 1) f[0][i][0] = 1;
        c[0][i] = a[0]>>i & 1;
        for (int j=1; j<n; ++j) c[j][i] = a[j] >> i & 1 ^ c[j-1][i];
    }
    for (int i=0, m=n-1; i<m; ++i) for (int j=0; j<32; ++j) if (f[i][j][0] || f[i][j][1]) {
        for (int k=0; k<=j; ++k) if (a[i+1] & 1ll<<k) {
            if (k<j && (a[i+1] & 1ll<<j)) {
                f[i+1][j][0] = (f[i+1][j][0] + (f[i][j][1]<<k)) % M;
                f[i+1][j][1] = (f[i+1][j][1] + (f[i][j][0]<<k)) % M;
            } else {
                f[i+1][j][0] = (f[i+1][j][0] + (f[i][j][0]<<k)) % M;
                f[i+1][j][1] = (f[i+1][j][1] + (f[i][j][1]<<k)) % M;
            }
        }
        for (int k=j+1; k<32; ++k) if (a[i+1] & 1ll<<k)
            f[i+1][k][c[i][k]] = (f[i+1][k][c[i][k]] + ((f[i][j][0] + f[i][j][1]) << j)) % M;
    }
    long long ans = 0;
    for (int i=31, m=n-1, t; i>=0; --i) {
        ans += f[m][i][t = (x>>i & 1)];
        if (c[m][i] ^ t) break;
    }
    return ans % M;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n>>x && n) cout << solve() << endl;
    return 0;
}