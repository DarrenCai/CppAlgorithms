/**
 * UVa11346
 * 概率
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(6);
    short t; cin >> t;
    while (t--) {
        double a, b, s; cin >> a >> b >> s;
        s /= a*b;
        if (s <= 0.) {
            cout << 100. << '%' << endl;
        } else if (s >= 1.) {
            cout << 0. << '%' << endl;
        } else {
            cout << (1. - s + s*log(s)) * 100 << '%' << endl;
        }
    }
    return 0;
}