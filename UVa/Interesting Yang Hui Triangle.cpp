/**
 * UVa1384/LA3700
 * 有趣的杨辉三角
 * Shanghai 2006
 * 需要运用组合数取模的Lucas定理推导，参见https://oi-wiki.org/math/number-theory/lucas/
 */

#include <iostream>
#include <iomanip>
using namespace std;

int p, n, kase = 0;

int solve() {
    int ans = 1;
    while (n) ans *= n%p + 1, n /= p;
    return ans % 10000;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> p >> n && (p || n))
        cout << "Case " << ++kase << ": " << setw(4) << setfill('0') << solve() << endl;
    return 0;
}