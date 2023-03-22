/**
 * UVa12230/LA4485
 * 过河
 * Wuhan 2009
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(3);
    short n, d, kase = 0;
    while (cin >>n>>d && d) {
        double t = .0;
        for (short i=0; i<n; ++i) {
            short x, l, v; cin >> x >> l >> v;
            d -= l; t += 2.*l/v;
        }
        t += d;
        cout << "Case " << ++kase << ": " << t << endl << endl;
    }
    return 0;
}