/**
 * LA4234
 */

#include <iostream>
using namespace std;

char a[19] = "";

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n; cin >> n;
    for (int i=1; i<=n; ++i) {
        short h, m, s; cin >> h >> a[0] >> m >> a[0] >> s;
        for (short i=0; i<6; ++i) {
            a[i] = h&(1<<(5-i)) ? '1' : '0';
            a[6+i] = m&(1<<(5-i)) ? '1' : '0';
            a[12+i] = s&(1<<(5-i)) ? '1' : '0';
        }
        cout << i << ' ';
        for (short i=0; i<18; ++i) cout << a[6*(i%3) + i/3];
        cout << ' ' << a << endl;
    }
    return 0;
}
