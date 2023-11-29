/**
 * UVa1513/LA5902
 * NWERC 2011
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 200200
int c[N], p[N>>1], t, a, m, n;

void add(int x, int k) {
    while (x < N) c[x] += k, x += x&-x;
}

int query(int x) {
    int s = 0;
    while (x > 0) s += c[x], x -= x&-x;
    return s;
}

void solve() {
    cin >> n >> m;
    memset(c, 0, sizeof(c));
    for (t=0; t<n; ++t) add(p[n-t] = t+1, 1);
    for (int i=0; i<m; ++i) {
        cin >> a;
        if (i) cout << ' ';
        cout << n - query(p[a]);
        add(p[a], -1); add(p[a] = ++t, 1);
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}