/**
 * UVa725/LA5362
 * 除法
 * Regionals 1990 >> North America - East Central NA
 */

#include <iostream>
using namespace std;

int n, kase = 0; bool vis[10];

bool check(int a, int b) {
    for (int i=0; i<10; ++i) vis[i] = false;
    if (b < 10000) vis[0] = true;
    for (int i=a; i; vis[i%10] = true, i/=10) if (vis[i%10]) return false;
    for (int i=b; i; vis[i%10] = true, i/=10) if (vis[i%10]) return false;
    cout << a << " / ";
    if (b < 10000) cout << 0;
    cout << b << " = " << n << endl;
    return true;
}

void solve() {
    if (kase ++) cout << endl;
    bool f = false;
    if (n > 1) for (int i=max((12345+n-1)/n, 1234), j=98765/n; i<=j; ++i) if (check(i*n, i)) f = true;
    if (!f) cout << "There are no solutions for " << n << '.' << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) solve();
    return 0;
}