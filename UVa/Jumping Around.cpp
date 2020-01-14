/**
 * UVa1621
 * 跳来跳去
 */

#include <iostream>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        short x = 0, a, b, c; cin >> a >> b >> c;
        cout << 0;
        if (c % 3 == 0) {
            for (short i=c/3; i; --i) cout << ' ' << (x += 3);
            cout << ' ' << ++x;
            for (short i=c/3; i; --i) cout << ' ' << (x -= 3);
            cout << ' ' << ++x;
            for (short i=c/3; i; --i) cout << ' ' << (x += 3);
            a -= 2;
        } else if (c % 3 == 1) {
            for (short i=c/3+1; i; --i) cout << ' ' << (x += 3);
            cout << ' ' << (x -= 2);
            for (short i=c/3; i; --i) cout << ' ' << (x -= 3);
            cout << ' ' << ++x;
            for (short i=c/3; i; --i) cout << ' ' << (x += 3);
            cout << ' ' << (x += 2);
            b -= 2; --a;
        } else {
            for (short i=c/3+1; i; --i) cout << ' ' << (x += 3);
            cout << ' ' << --x;
            for (short i=c/3; i; --i) cout << ' ' << (x -= 3);
            cout << ' ' << --x;
            for (short i=c/3+1; i; --i) cout << ' ' << (x += 3);
            a -= 2;
        }
        while (--a) cout << ' ' << ++x;
        short h = (b+1) >> 1;
        for (short i=0; i<h; ++i) cout << ' ' << (x += 2);
        cout << ' ' << (h == b>>1 ? ++x : --x);
        for (short i=b>>1; i; --i) cout << ' ' << (x -= 2);
        cout << endl;
    }
    return 0;
}