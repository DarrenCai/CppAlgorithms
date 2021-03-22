/**
 * UVa12034
 * 比赛名次
 */

#include <iostream>
using namespace std;

#define N 1002
#define M 10056
short c[N][N], f[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    f[0] = 1;
    for (short i=1; i<N; ++i) {
        f[i] = 0; c[i][0] = c[i][i] = 1;
        for (short j=1; j<<1 <= i; ++j) c[i][j] = c[i][i-j] = (c[i-1][j-1] + c[i-1][j])%M;
        for (short j=1; j<=i; ++j) f[i] = (f[i] + int(c[i][j])*f[i-j])%M;
    }
    short t; cin >> t;
    for (short kase=1; kase<=t; ++kase) {
        short n; cin >> n;
        cout << "Case " << kase << ": " << f[n] << endl;
    }
    return 0;
}