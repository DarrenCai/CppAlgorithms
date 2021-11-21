/**
 * p2765 魔术球问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 61
short ans[N][N][N] = {0}, c[N][N] = {0}, t[N] = {0}, n;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (short n=1; n<N; ++n) {
        memcpy(ans[n], ans[n-1], sizeof(ans[n])); memcpy(c[n], c[n-1], sizeof(c[n]));
        short p = n*n; t[n] = ans[n][n][c[n][n]++] = t[n-1]+1;
        for (short i=1; i<=n; ++i) if (p > (ans[n][i][c[n][i]-1]<<1))
            t[n] = max(t[n], ans[n][i][c[n][i]++] = p - ans[n][i][c[n][i]-1]);
    }
    while (cin >> n) {
        cout << t[n] << endl;
        for (short i=1; i<=n; ++i) {
            cout << ans[n][i][0];
            for (short j=1; j<c[n][i]; ++j) cout << ' ' << ans[n][i][j];
            cout << endl;
        }
    }
    return 0;
}