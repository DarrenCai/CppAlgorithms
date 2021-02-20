/**
 * UVa1371
 * 周期
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 5020
#define N 60

short d[M][N], m, n; char x[M], y[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (short i=0; i<N; ++i) d[0][i] = i;
    short t; cin >> t;
    while (t--) {
        cin >> y+1 >> x+1;
        m = strlen(x+1); n = strlen(y+1);
        short l=0, r=n;
        while (l <= r) {
            short mid = (l+r) >> 1;
            for (short i=1; i<=m; ++i) {
                d[i][0] = i;
                for (short j=1; j<=n; ++j) {
                    if (x[i] == y[j]) d[i][j] = d[i-1][j-1];
                    else d[i][j] = 1 + min(d[i-1][j-1], min(d[i-1][j], d[i][j-1]));
                }
                d[i][0] = d[i][n] <= mid ? 0 : N;
            }
            d[m][n] > mid ? l = mid+1 : r = mid-1;
        }
        cout << l << endl;
    }
    return 0;
}