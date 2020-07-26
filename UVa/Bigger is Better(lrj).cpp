/**
 * UVa12105
 * 越大越好
 */

#include <iostream>
using namespace std;

#define N 105
#define M 3005
short n, m, t, c[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6}, d[N][M], b[N][M];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short kase = 0;
    while (cin >> n >> m && n) {
        for (short i=0; i<=n; ++i) for (short j=0; j<m; ++j) {
            short &ans = d[i][j]; ans = b[i][j] = -1;
            if (j == 0) ans = 0;
            for (short v=9; v>=0; --v) if (c[v] <= i) {
                short t = d[i-c[v]][(10*j+v)%m];
                if (t >= 0 && t+1 > ans) ans = t+1, b[i][j] = v;
            }
        }
        cout << "Case " << ++kase << ": ";
        if (d[n][0] <= 0) cout << -1;
        else {
            while (b[n][0] == 0 && d[n][0] > 1) n -= 6;
            for (short i=n, j=0, v; d[i][j]; i-=c[v], j=(10*j+v)%m) cout << (v = b[i][j]);
        }
        cout << endl;
    }
    return 0;
}