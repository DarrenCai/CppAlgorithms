/**
 * UVa11605
 * 三维网格中的灯
 */

#include <iostream>
#include <iomanip>
using namespace std;

double pow(double p, int k) {
    if (k == 1) return p;
    double np = pow(p, k>>1); np *= 2*(1-np);
    return k&1 ? np*(1-p) + (1-np)*p : np;
}

double solve() {
    int m, n, p, k; cin >> m >> n >> p >> k;
    if (k == 0) return 0;
    long long v = m*n*p; v *= v;
    double ans = 0;
    for (int x=(m+1)>>1; x>0; --x) for (int y=(n+1)>>1; y>0; --y) for (int z=(p+1)>>1; z>0; --z) {
        double f = (2*x*(m-x+1)-1.)*(2*y*(n-y+1)-1)*(2*z*(p-z+1)-1) / v;
        ans += (2*x>m ? 1 : 2)*(2*y>n ? 1 : 2)*(2*z>p ? 1 : 2) * pow(f, k);
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(10);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Case " << kase << ": " << solve() << endl;
    return 0;
}