/**
 * poj2096
 * 找BUG
 * 2004-2005 ACM-ICPC, NEERC, Northern Subregional Contest
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 1002
double f[N][N]; int n, s;

double solve() {
    f[n][s] = 0;
    for (int i=n-1; i>=0; --i) f[i][s] = f[i+1][s] + 1.*n/(n-i);
    for (int i=s-1; i>=0; --i) f[n][i] = f[n][i+1] + 1.*s/(s-i);
    for (int i=n-1; i>=0; --i) for (int j=s-1; j>=0; --j) {
        double p = 1.*i/n, q = 1.*j/s;
        f[i][j] = (1 + p*(1-q)*f[i][j+1] + (1-p)*q*f[i+1][j] + (1-p)*(1-q)*f[i+1][j+1]) / (1 - p*q);
    }
    return f[0][0];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(4);
    while (cin>>n>>s) cout << solve() << endl;
    return 0;
}