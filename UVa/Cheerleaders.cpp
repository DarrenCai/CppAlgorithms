/**
 * UVa11806
 * 拉拉队
 * 注意：排列组合有两个递推式
 *      C[n+1][k+1] = C[n][k] + C[n][k+1]    
 *      C[n][k+1] = C[n][k]*(n-k)/(k+1)
 * 第一个递推式效率更高，并且在需要取模时第二个递推式不可用，只能用第一个
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 1000007
#define N 401
int c[N][N];

int solve() {
    int m, n, k; cin >> m >> n >> k;
    if (k<2 || k>m*n) return 0;
    return
        (M + (c[m*n][k] - 2*c[(m-1)*n][k] - 2*c[(n-1)*m][k]
                + 4*c[(m-1)*(n-1)][k] + c[m*(n-2)][k] + c[n*(m-2)][k]
                - 2*c[(m-1)*(n-2)][k] - 2*c[(n-1)*(m-2)][k] + c[(m-2)*(n-2)][k]
             ) % M
        ) % M;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    memset(c, 0, sizeof(c)); c[0][0] = 1;
    for (int i=1; i<N; ++i) {
        c[i][0] = c[i][i] = 1;
        for (int j=1, k=(i+1)>>1; j<=k; ++j) c[i][j] = c[i][i-j] = (c[i-1][j-1] + c[i-1][j]) % M;
    }
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Case " << kase << ": " << solve() << endl;
    return 0;
}