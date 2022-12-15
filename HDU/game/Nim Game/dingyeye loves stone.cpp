/**
 * HDU5996
 * http://acm.hdu.edu.cn/showproblem.php?pid=5996
 * hdu的oj通常要注意io的优化
 * 本体是阶梯Nim博弈
 */

#include <iostream>
using namespace std;

#define N 100010
int d[N], s, n;

void solve() {
    cin >> n;
    for (int i=s=0; i<n; ++i) d[i] = 0;
    for (int i=1, u; i<n; ++i) cin >>u, d[i] = d[u] + 1;
    for (int i=0, a; i<n; ++i) cin >> a, s ^= d[i]&1 ? a : 0;
    cout << (s ? "win\n" : "lose\n");
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}