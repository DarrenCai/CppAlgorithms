/**
 * UVa10237
 * 互不攻击的象
 */

#include <iostream>
using namespace std;

#define N 31
long long f[N][2][N][2][N] = {0}; int n, k;

long long solve() {
    if (n == 1) return k<=1;
    if (k > 2*n-2) return 0;
    if (n & 1) {
        long long (&r1)[N] = f[n][0][1][1], (&r2)[N] = f[n-1][1][n>3 ? 2 : 0][1], ans = 0;
        for (int i=0; i<=k && i<n; ++i) ans += r1[i]*r2[k-i];
        return ans;
    }
    long long (&r)[N] = f[n][0][n>2 ? 2 : 0][1], ans = 0;
    for (int i=0; i<=k && i<n; ++i) ans += r[i]*r[k-i];
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int h1=2; h1<N; ++h1) for (int c1=0; c1<2; ++c1) {
        f[h1][c1][0][0][0] = f[h1][c1][0][1][0] = 1;
        f[h1][c1][0][0][1] = f[h1][c1][0][1][1] = (c1+1)*h1;
        if (c1) f[h1][c1][0][0][2] = f[h1][c1][0][1][2] = h1*(h1-1);
        for (int h2 = h1-2; h2>0; h2 -= 2) for (int c2=0; c2<2; ++c2) {
            f[h1][c1][h2][c2][0] = 1;
            for (int k=1, m=min(h1, h1-h2+c1+c2); k<=m; ++k) {
                f[h1][c1][h2][c2][k] = f[h1][c1][c2 ? h2 : (h2+2<h1 ? h2+2 : 0)][!c2][k]
                    + h2 * f[h1-1][c1][c2 ? (h2>1 ? h2-1 : (h1>3 ? 2 : 0)) : (h2+2<h1 ? h2+1 : 0)][h2>1 ? !c2 : 1][k-1];
            }
        }
    }
    while (cin>>n>>k && n) cout << solve() << endl;
    return 0;
}