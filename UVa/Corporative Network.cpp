/**
 * UVa1329/LA3027
 * 合作网络
 * SEERC 2004
 */

#include <iostream>
using namespace std;

#define N 20005
int f[N], d[N], u, v, n, t; char ch;

int find(int x) {
    if (f[x] == x) return x;
    int p = f[x];
    f[x] = find(p);
    d[x] += d[p];
    return f[x];
}

void solve() {
    cin >> n;
    for (int i=1; i<=n; ++i) f[i] = i, d[i] = 0;
    while (cin>>ch && ch!='O') {
        cin >> u;
        if (ch == 'I') {
            cin >> v;
            f[u] = v;
            d[u] = abs(u-v)%1000;
        } else {
            find(u);
            cout << d[u] << endl;
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> t;
    while (t--) solve();
    return 0;
}