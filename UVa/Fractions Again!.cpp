/**
 * UVa10976
 * 分数拆分
 */

#include <iostream>
using namespace std;

#define N 10002
int x[N], y[N], k;

void solve() {
    int t = 0;
    for (int i=k+1, m=k<<1; i<=m; ++i) if (k*i % (i-k) == 0) x[t] = k*i / (i-k), y[t++] = i;
    cout << t << endl;
    for (int i=0; i<t; ++i) cout << 1 << '/' << k << " = " << 1 << '/' << x[i] << " + " << 1 << '/' << y[i] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> k) solve();
    return 0;
}