/**
 * UVa11987
 * 几乎就是并查集
 */

#include <iostream>
using namespace std;

#define N 200100
int f[N], c[N], m, n; long long s[N];

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

void solve() {
    for (int i=1; i<=n; ++i) c[f[i] = f[n+i] = n+i] = 1, s[n+i] = i;
    while (m--) {
        int t, p, q; cin >> t >> p;
        if (t == 1) {
            cin >> q;
            int x = find(p), y = find(q);
            if (x != y) c[y] += c[x], s[y] += s[x], f[x] = y, c[x] = s[x] = 0;
        } else if ( t== 2) {
            cin >> q;
            int x = find(p), y = find(q);
            if (x != y) ++c[y], s[y] += p, f[p] = y, --c[x], s[x] -= p;
        } else f[0] = find(p), cout << c[f[0]] << ' ' << s[f[0]] << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) solve();
    return 0;
}