/**
 * UVa1328/LA3026
 * 周期
 * SEERC 2004
 */

#include <iostream>
using namespace std;

#define N 1000010
char s[N]; int f[N], n, kase = 0;

void solve() {
    cin >> s;
    f[0] = -1;
    for (int i=0, j=-1; i<n; f[++i] = ++j) while (j>=0 && s[j] != s[i]) j = f[j];
    cout << "Test case #" << ++kase << endl;
    for (int i=2; i<=n; ++i) if (f[i] && i % (i-f[i]) == 0) cout << i << ' ' << i / (i-f[i]) << endl;
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin>>n && n) solve();
    return 0;
}