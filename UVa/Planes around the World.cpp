/**
 * UVa10640
 * 飞机环球
 */

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    for (short kase = 1; kase <= t; ++kase) {
        cout << "Case " << kase << ": ";
        short a, b; cin >> a >> b;
        if (a >= b) {
            cout << 1 << endl;
        } else if (3*a <= b) {
            cout << -1 << endl;
        } else {
            short x = ceil(2.*(b-a)/(3*a-b));
            short y = max(ceil(2.*(b*(x+2)-2*a*(x+1))/((a-b)*(x+2)+2*a*(x+1))), 0.) + x + 1;
            cout << (y>1000 ? -1 : y) << endl;
        }
    }
    return 0;
}