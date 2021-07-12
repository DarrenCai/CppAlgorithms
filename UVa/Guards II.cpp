/**
 * UVa12590
 * 守卫II
 */

#include <iostream>
using namespace std;

#define N 105
#define M 1000000007ll

long long c[(N-1)*(N-1)+1][N] = {0}, d[N][N][N] = {0}, dd[N][N][N] = {0};

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int n=0, nn=(N-1)*(N-1); n<=nn; ++n) {
        c[n][0] = 1;
        for (int k=1, kk=min(n,N-1); k<=kk; ++k) c[n][k] = (c[n-1][k] + c[n-1][k-1]) % M;
    }
    for (short i=1; i<N; ++i) dd[0][i][0] = dd[i][0][0] = 1;
    for (short k=1; k<N; ++k) for (short m=1; m<=k; ++m) for (short n=1; n<N; ++n) {
        long long& ref = dd[m][n][k];
        for (short i=min(n,k); i>0; --i) ref = (ref + c[n][i]*dd[m-1][n][k-i]) % M;
    }
    for (short k=1; k<N; ++k) for (short m=1; m<=k; ++m) for (short n=1; n<=k; ++n) if (m*n >= k) {
        long long cnt = 0, cc = 0;
        for (short i=m-k/n-(k%n ? 1 : 0); i>0; --i)
            cnt = (cnt + c[m][i]*dd[m-i][n][k]) % M;
        for (short i=n-k/m-(k%m ? 1 : 0); i>0; --i)
            cnt = (cnt + c[n][i]*d[m][n-i][k]) % M;
        d[m][n][k] = (c[m*n][k] + M - cnt) % M;
    }
    short t; cin >> t;
    for (short kase=1; kase <= t; ++kase) {
        short m, n, k; cin >> m >> n >> k;
        cout << "Case " << kase << ": ";
        if (k <= (m-1)*(n-1)) {
            long long cnt = 0;
            for (short i=m-1; i>0; --i) for (short j=n-1; j>0; --j) {
                long long cc = c[m][i]*c[n][j] - (i>1 && j>1 ? c[m-2][i-2]*c[n-2][j-2] : 0);
                cnt = (cnt + cc%M * d[i][j][k]) % M;
            }
            cout << (c[m*n][k] + M - cnt) % M << endl;
        } else cout << c[m*n][k] << endl;
    }
    return 0;
}
