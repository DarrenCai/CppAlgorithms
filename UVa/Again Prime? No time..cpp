/**
 * UVa10780
 * 幂和阶乘
 */

#include <iostream>
using namespace std;

#define M 5005
#define N 10010
int c[M][N]; bool f[M] = {0};

int solve() {
    int m, n, k = 0; cin >> m >> n;
    for (int i=2; i*i<=m; ++i) if (m%i == 0) {
        int c1 = 0;
        while (m%i == 0) ++ c1, m /= i;
        if (!(c1 = c[i][n] / c1)) return 0;
        k = k==0 ? c1 : min(k, c1);
    }
    if (m > 1) {
        if (!c[m][n]) return 0;
        k = k==0 ? c[m][n] : min(k, c[m][n]);
    }
    return k;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=2; i<70; ++i) if (!f[i]) for (int j=i<<1; j<M; j+=i) f[j] = true;
    for (int i=2; i<M; ++i) if (!f[i]) {
        c[i][1] = 0;
        for (int j=2; j<N; ++j) {
            c[i][j] = c[i][j-1];
            for (int x=j; x%i == 0; x /= i) ++c[i][j];
        }
    }
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) {
        cout << "Case " << kase << ':' << endl;
        int k = solve();
        k ? cout << k << endl : cout << "Impossible to divide" << endl;
    }
    return 0;
}