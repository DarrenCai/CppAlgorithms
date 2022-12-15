/**
 * HDU1846
 * http://acm.hdu.edu.cn/showproblem.php?pid=1846
 * 勇敢者的游戏
 */

#include <iostream>
using namespace std;

void solve() {
    int m, n; cin >> n >> m;
    cout << (n%(m+1) ? "first" : "second") << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}