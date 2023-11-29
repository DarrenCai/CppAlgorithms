/**
 * UVa12299
 * 带循环移动的RMQ
 */

#include <iostream>
#include <cstring>
using namespace std;

unsigned int a[1<<17], x[1<<18], x1, x2, n, p, q;

void set(int o, int l, int r) {
    if (l < r) {
        int m = (l+r)>>1, lc = o<<1, rc = lc+1;
        p <= m ? set(lc, l, m) : set(rc, m+1, r);
        x[o] = min(x[lc], x[rc]);
    } else x[o] = a[p];
}

unsigned int query(int o, int l, int r) {
    if (l>=x1 && r<=x2) return x[o];
    unsigned int m = (l+r)>>1, lc = o<<1, rc = lc+1, ans = -1;
    if (x1 <= m) ans = query(lc, l, m);
    if (x2 > m) ans = min(ans, query(rc, m+1, r));
    return ans;
}

void solve() {
    cin >> n >> q;
    memset(x, -1, sizeof(x));
    for (p=1; p<=n; ++p) cin >> a[p], set(1, 1, n);
    while (q--) {
        char c; cin >> c;
        if (c == 'q') {
            cin >> c >> c >> c >> c >> c >> x1 >> c >> x2 >> c;
            cout << query(1, 1, n) << endl;
        } else {
            cin >> c >> c >> c >> c >> c >> p;
            unsigned x1 = a[p];
            while (cin.get() == ',') cin >> x2, a[p] = a[x2], set(1, 1, n), p = x2;
            a[p] = x1; set(1, 1, n);
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}