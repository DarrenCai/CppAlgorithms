/**
 * UVa12036
 * 稳定的网格
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 105
short cnt[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    for (short kase=1; kase<=t; ++kase) {
        memset(cnt, 0, sizeof(cnt));
        short n; cin >> n; bool ok = true;
        for (short i=0; i<n; ++i) for (short j=0; j<n; ++j) {
            short v; cin >> v; if (++ cnt[v] > n) ok = false;
        }
        cout << "Case " << kase << ": " << (ok ? "yes" : "no") << endl;
    }
    return 0;
}