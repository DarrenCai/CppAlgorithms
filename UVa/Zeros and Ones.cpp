/**
 * UVa12063
 * 零和一
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 64
#define K 110
unsigned long long d[N][N>>1][K], p[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    p[0] = 1; for (short i=1; i<N; ++i) p[i] = p[i-1]<<1;
    short t; cin >> t;
    for (short kase=1; kase<=t; ++kase) {
        short n, k; cin >> n >> k;
        if (!(n&1) && k) {
            memset(d, 0, sizeof(d));
            d[0][0][p[--n]%k] = 1;
            short nn = n>>1;
            for (short i=0; i<n; ++i) for (short j=0, ii=min(i,nn); j<=ii; ++j) for (short r=0; r<k; ++r) {
                d[i+1][j][r] += d[i][j][r];
                if (j<nn) d[i+1][j+1][(r+p[n-i-1])%k] += d[i][j][r];
            }
            cout << "Case " << kase << ": " << d[n][nn][0] << endl;
        } else cout << "Case " << kase << ": 0" << endl;
    }
    return 0;
}