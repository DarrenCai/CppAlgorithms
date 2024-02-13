/**
 * UVa10566
 * 交叉的梯子
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double x, y, c;

double solve() {
    if (x == y) return sqrt(x*x - 4*c*c);
    x *= x; y *= y;
    double s = .5*c, t = min(x, y)-c*c, a = sqrt((x-t)), b = sqrt((y-t)), f = c/a + c/b - 1, d = s/a/a/a + s/b/b/b;
    while (abs(f) > 1e-6) {
        t -= f/d; a = sqrt((x-t)); b = sqrt((y-t)); f = c/a + c/b - 1; d = s/a/a/a + s/b/b/b;
    }
    return sqrt(t);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(3);
    while (cin >> x >> y >> c) cout << solve() << endl;
    return 0;
}
