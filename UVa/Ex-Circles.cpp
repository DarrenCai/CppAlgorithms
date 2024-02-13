/**
 * UVa11731
 * 外切圆
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int a, b, c, kase = 0;

void solve() {
    double x = (b*b+c*c-a*a)/2./b/c, y = (a*a+c*c-b*b)/2./a/c, z = (a*a+b*b-c*c)/2./a/b;
    x = sqrt((1-x)/(1+x)); y = sqrt((1-y)/(1+y)); z = sqrt((1-z)/(1+z));
    double r1 = a/(y+z), r2 = b/(x+z), r3 = c/(x+y);
    x = atan(x); y = atan(y); z = atan(z);
    double p = (a+b+c)/2., s = (a*r1 + b*r2 + c*r3)/2 + sqrt(p*(p-a)*(p-b)*(p-c));
    cout << "Case " << ++kase << ": " << s << ' ' << (r1*r1*(y+z) + r2*r2*(x+z) + r3*r3*(x+y))/2 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(2);
    while (cin >> a >> b >> c && a) solve();
    return 0;
}