/**
 * HDU2149
 * http://acm.hdu.edu.cn/showproblem.php?pid=2149
 */

#include <iostream>
using namespace std;

int m, n;

void solve() {
    int r = m % (n+1);
    if (r) {
        if (m <= n) {
            cout << m;
            while (++m <= n) cout << ' ' << m;
        } else cout << r;
        cout << endl;
    } else cout << "none" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>m>>n) solve();
    return 0;
}