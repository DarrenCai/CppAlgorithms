/**
 * MemSQL Start[c]UP 3.0 - Round 2 and Codeforces Round 437 (Div. 1)
 * https://codeforces.com/contest/866/problem/C
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 52
#define R 5304
double d[N][R]; int f[N], s[N], p[N], n, r;

bool check(double v) {
    for (int i=n-1; i>0; --i) for (int j=0; j<=r; ++j) {
        double &x = d[i][j] = v;
        if (j+f[i] <= r) 
            x = min(x, (f[i]+d[i+1][j+f[i]])*p[i]/100 + (j+s[i] <= r ? s[i]+d[i+1][j+s[i]] : s[i]+v)*(100-p[i])/100);
    }
    return (f[0]+d[1][f[0]])*p[0]/100+(s[0] <= r ? s[0]+d[1][s[0]] : s[0]+v)*(100-p[0])/100 <= v;
}

double solve() {
    double low = .0, high = __FLT_MAX__;
    for (int i=0; i<n; ++i) cin >> f[i] >> s[i] >> p[i], low += f[i];
    for (int i=0; i<=r; ++i) d[n][i] = .0;
    while (__builtin_fabs(high-low)/max(1., low) >= 1e-12) {
        double mid = (low + high)/2;
        check(mid) ? high = mid : low = mid;
    }
    return low;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(9);
    while (cin >> n >> r) cout << solve() << endl;
    return 0;
}