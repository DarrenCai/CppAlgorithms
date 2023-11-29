/**
 * UVa1232/LA4108
 * 轮廓线
 * Singapore 2007
 */

#include <iostream>
using namespace std;

#define X 100050
int x[1<<18], y[1<<18], n, x1, x2, h;

int query(int o, int l, int r) {
    if (h < x[o]) return 0;
    if (l >= x1 && r <= x2 && h >= y[o]) {
        x[o] = y[o] = h;
        return r-l+1;
    }
    int m = (l+r)>>1, lc = o<<1, rc = lc+1, cc = 0;
    if (x[o] == y[o]) x[lc] = y[lc] = x[rc] = y[rc] = x[o];
    if (x1 <= m) cc += query(lc, l, m);
    if (x2 > m) cc += query(rc, m+1, r);
    x[o] = min(x[lc], x[rc]); y[o] = max(y[lc], y[rc]);
    return cc;
}

void solve() {
    cin >> n;
    x[1] = y[1] = 0;
    int ans = 0;
    while (n--) cin >> x1 >> x2 >> h, --x2, ans += query(1, 1, X);
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}