/**
 * UVa11427
 * 玩纸牌
 */

#include <iostream>
using namespace std;

#define N 102
double f[N][N];

int solve() {
    int p, d, n; cin >> p; cin.get(); cin >> d >> n;
    for (int i=1; i<=n; ++i) {
        f[i][0] = f[i-1][0] * (d-p) / d;
        for (int j = i*p/d; j>0; --j) {
            f[i][j] = f[i-1][j-1] * p / d;
            if (j*d <= (i-1)*p) f[i][j] += f[i-1][j] * (d-p) / d;
        }
    }
    double q = f[n][0];
    for (int i = n*p/d; i>0; --i) q += f[n][i];
    return 1. / q + .001;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    f[0][0] = 1.0;
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Case #" << kase << ": " << solve() << endl;
    return 0;
}