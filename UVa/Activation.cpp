/**
 * UVa1498/LA5721
 * 软件激活排队
 * Beijing 2011
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 2005
double f[N], s[N], pow[N], p0, p1, p2; int m, n, k;

double solve() {
    cin >> p0 >> p0 >> p1 >> p2;
    double t = p0 + p1 + p2;
    if (t==0. || p0==t) return 0.;
    p0 /= t; p1 /= t; p2 /= t;
    f[1] = p2 / (1-p0); s[0] = 0.; pow[1] = p0;
    for (int i=2; i<=m; ++i) {
        pow[i] = p0*pow[i-1];
        for (int j=1; j<i; ++j) s[j] = p0*s[j-1] + f[j];
        for (int j=1; j<=i; ++j) {
            f[j] = p1*s[j-1] + p1*s[i-1]*pow[j] / (1-pow[i]) + 
                    p2*(1-pow[min(i, k)])/(1-p0)*pow[j<=k ? j+max(i,k)-k : j-k] / (1-pow[i]);
            if (j <= k) f[j] += p2 * (1-pow[j]) / (1 - p0);
        }
    }
    return f[n];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(5);
    while (cin >> m >> n >> k) cout << solve() << endl;
}