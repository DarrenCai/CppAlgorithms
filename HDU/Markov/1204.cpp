/**
 * HDU1204
 * http://acm.hdu.edu.cn/showproblem.php?pid=1204
 * 糖果大战
 * 马尔可夫过程
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int m, n; double p, q;

double solve() {
    if (n==0) return 0;
    if (m==0) return 1;
    if (p==0 || q==1) return 0;
    if (q==0 || p==1) return 1;
    if (p == q) return 1.*n/(m+m);
    double x = q*(1-p)/p/(1-q);
    return (1-pow(x, n)) / (1-pow(x, m+n));
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(2);
    while (cin >> n >> m >> p >> q) cout << solve() << endl;
    return 0;
}