/**
 * P2765 魔术球问题
 */

#include <iostream>
using namespace std;

#define N 61
int ans[N][N][N] = {0}, c[N][N] = {0}, t[N] = {0}, n;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int n=1; n<N; ++n) {
        for (int i=1; i<n; ++i) for (int j=0, k=c[n][i]=c[n-1][i]; j<k; ++j) ans[n][i][j] = ans[n-1][i][j];
        int p = n*n; t[n] = ans[n][n][c[n][n]++] = t[n-1]+1;
        for (int i=1, j; i<=n; ++i) if (p > (j = ans[n][i][c[n][i]-1]) << 1)
            t[n] = max(t[n], ans[n][i][c[n][i]++] = p - j);
    }
    while (cin >> n) {
        cout << t[n] << endl;
        for (int i=1; i<=n; ++i) {
            cout << ans[n][i][0];
            for (int j=1; j<c[n][i]; ++j) cout << ' ' << ans[n][i][j];
            cout << endl;
        }
    }
    return 0;
}