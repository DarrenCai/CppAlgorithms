/**
 * UVa11637
 * 背单词
 */

#include <iostream>
#include <iomanip>
using namespace std;

int n, k, kase = 0;

double solve() {
    if (n == 1) return 0;
    if (3*k >= n) return n;
    int m = min(n-3*k-1, k); double s = 2, t = 2;
    for (int i=1; i<=m; ++i, s+=t) t = t*(n-3*k-i)/(n-k-i);
    if (++m > k) s += (n-2*m)*t/2;
    for (int i=1; i<=k; ++i) s = s*(n-2*k-i)/(n-i);
    return n-s;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(4);
    while (cin>>n>>k && n) cout << "Case " << ++kase << ": " << solve() << endl;
    return 0;
}