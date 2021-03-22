/**
 * UVa12034
 * 比赛名次
 */

#include <iostream>
using namespace std;

#define N 1002
#define M 10056
short d[N][N], f[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    f[1] = d[1][1] = 1;
    for (int i=2; i<N; ++i) {
        f[i] = ((d[i][1] = 1) + (d[i][i] = i*d[i-1][i-1]%M))%M;
        for (int j=2; j<i; ++j) f[i] = (f[i] + (d[i][j] = j*(d[i-1][j-1]+d[i-1][j])%M))%M;
    }
    short t; cin >> t;
    for (short kase=1; kase<=t; ++kase) {
        short n; cin >> n;
        cout << "Case " << kase << ": " << f[n] << endl;
    }
    return 0;
}