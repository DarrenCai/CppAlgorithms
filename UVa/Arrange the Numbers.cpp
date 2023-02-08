/**
 * UVa11481
 * 重排问题
 */

#include <iostream>
using namespace std;

#define M 1000000007
#define N 1002
long long c[N][N], f[N][N], p[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    f[0][0] = c[0][0] = p[0] = 1; for (int i=1; i<N; ++i) p[i] = p[i-1]*i%M;
    for (int i=1; i<N; ++i) {
        c[i][0] = c[i][i] = 1;
        for (int j=1; j<i; ++j) c[i][j] = (c[i-1][j] + c[i-1][j-1]) % M;
    }
    for (int i=1; i<N; ++i) {
        f[i][0] = p[i]; f[i][1] = (i-1)*p[i-1] % M;
        for (int j=2; j<=i; ++j) f[i][j] = ((j-1)*f[i-1][j-2] + (i-j)*f[i-1][j-1]) % M;
    }
    int t; cin >> t;
    for (int kase=1, m, n, k; kase<=t; ++kase) {
        cin >> n >> m >> k;
        cout << "Case " << kase << ": " << c[m][k]*f[n-k][m-k] % M << endl;
    }
    return 0;
}