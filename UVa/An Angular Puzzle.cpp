/**
 * UVa12301
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define dtr 0.01745329251994329508887757483l

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(2);
    int a, b, c, d, e;
    while (cin >> a >> b >> c >> d >> e && a) {
        if (a+b+c+d+e != 180) {
            cout << "Impossible" << endl;
        } else {
            double f = dtr*a, g = dtr*b, h = dtr*c, i = dtr*d, j = dtr*e;
            double k = sin(f+i)*sin(h)*sin(i)/sin(f+g)/sin(g)/sin(j), x = h+j, y = k+cos(x);
            cout << atan2(sin(x), y)/dtr << endl;
        }
    }
    return 0;
}
