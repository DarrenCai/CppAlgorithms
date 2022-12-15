/**
 * HDU2176
 * http://acm.hdu.edu.cn/showproblem.php?pid=2176
 * 取(m堆)石子游戏
 */

#include <iostream>
using namespace std;

#define N 200020
int a[N], n;

int highbit(int x) {
    for (int i=1; i<32; i<<=1) x |= x>>i;
    return (x+1) >> 1;
}

void solve() {
    int s = 0;
    for (int i=0; i<n; ++i) cin >> a[i], s ^= a[i];
    if (s == 0) {
        cout << "No" << endl;
        return;
    }
    cout << "Yes" << endl;
    for (int i=0, b=highbit(s); i<n; ++i) if (a[i] & b) cout << a[i] << ' ' << (a[i]^s) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n && n) solve();
    return 0;
}