/**
 * UVa11021
 * 麻球繁衍
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define N 1010
double f[N], p[N]; int n, k, m, kase = 0;

void solve() {
    cin >> n >> k >> m;
    for (int i=0; i<n; ++i) cin >> p[i];
    f[0] = 0; f[1] = p[0];
    for (int i=2; i<=m; ++i) {
        double x = f[i-1]; f[i] = 0;
        for (int j=n-1; j>=0; --j) f[i] = f[i]*x + p[j];
    }
    cout << "Case #" << ++kase << ": " << pow(f[m], k) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(7);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}