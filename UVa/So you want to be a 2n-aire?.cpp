/**
 * UVa10900
 * 你想当2^n元富翁吗?
 */

#include <iostream>
#include <iomanip>
using namespace std;

double solve(int n, double t) {
    double ans = 1.;
    while (n--) {
        double x = max(.5/ans, t);
        ans = (x-t + (1-x)*(1+x)*ans) / (1-t);
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(3);
    int n; double t;
    while (cin>>n>>t && n) cout << solve(n, t) << endl;
    return 0;
}