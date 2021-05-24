/**
 * UVa11982
 * 名次表的变化
 * 还可以尝试求二分图完美匹配的个数
 */

#include <iostream>
using namespace std;

#define N 1010
#define M 1000000007

char s[N]; int d[N][N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    d[0][0] = 1;
    for (short i=1; i<N; ++i) d[0][i] = 0;
    short t; cin >> t;
    for (short kase=1; kase<=t; ++kase) {
        cin >> s;
        short n=0, c=0;
        while (s[n])
            if (s[n++] == 'U') {
                d[n][0] = 0; d[n][++c] = d[n-1][c];
                for (long long j=1; j<c; ++j) d[n][j] = (d[n-1][j-1] + d[n-1][j]*j) % M;
            } else if (s[n-1] == 'D') {
                d[n][c] = (long long)d[n-1][c]*c % M;
                for (long long j=0; j<c; ++j) d[n][j] = (d[n-1][j+1]*(j+1)*(j+1) + d[n-1][j]*j) % M;
            } else for (short j=0; j<=c; ++j) d[n][j] = d[n-1][j];
        cout << "Case " << kase << ": " << d[n][0] << endl;
    }
    return 0;
}
