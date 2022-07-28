/**
 * UVa1312/LA2689
 * 球场
 * NEERC 2002
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 110
int x[N], y[N], n, w, h;
struct point {
    int x, y;
    bool operator< (const point& rhs) const {
        return y<rhs.y || (y==rhs.y && x<rhs.x);
    }
} s[N];

void solve() {
    cin >> n >> w >> h; x[n] = 0; x[n+1] = w;
    for (int i=0; i<n; ++i) cin >> s[i].x >> s[i].y, x[i] = s[i].x;
    sort(s, s+n); sort(x, x+n+2);
    int m = unique(x, x+n+2) - x, ansl = 0, ansx, ansy;
    for (int i=0; i<m; ++i) for (int j=i+1; j<m; ++j) {
        int l = x[i], r = x[j], t = 0, l1 = r-l; y[0] = 0;
        for (int k=0; k<n; ++k) if (s[k].x>l && s[k].x<r && s[k].y>y[t]) y[++t] = s[k].y;
        if (y[t] < h) y[++t] = h;
        for (int k=1; k<=t; ++k) {
            int ll = min(l1, y[k]-y[k-1]);
            if (ll > ansl) {
                ansl = ll; ansx = l; ansy = y[k-1];
            }
        }
    }
    cout << ansx << ' ' << ansy << ' ' << ansl << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int kase=0; kase<t; ++kase) {
        if (kase) cout << endl;
        solve();
    }
    return 0;
}