/**
 * UVa11646
 * 运动场的跑道
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int a, b, kase = 0; char _;

void solve() {
    double x = 200/(a + sqrt(a*a + b*b)*atan2(b, a));
    cout << "Case " << ++kase << ": " << a*x << ' ' << b*x << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(5);
    while (cin >> a >> _ >> b) solve();
    return 0;
}