/**
 * UVa1468/LA4851
 * 餐厅
 * Daejon 2010
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 60200
int a[N], m, n;
struct point {
    int x, y;
    bool operator< (const point& rhs) const {
        return x<rhs.x || (x==rhs.x && y<rhs.y);
    }
} s[N];

int solve() {
    cin >> m >> n;
    for (int i=0; i<n; ++i) cin >> s[i].x >> s[i].y;
    int y = s[0].y, x1 = min(s[0].x, s[1].x), x2 = max(s[0].x, s[1].x), ans = 0;
    sort(s, s+n);
    for (int i=0, d=m, x=s[0].x; i<n && x<=x2; ++i) {
        while (s[i].x > x) a[x++] = d++;
        if (s[i].x < x2) d = min(d, abs(s[i].y - y) - 1);
    }
    for (int i=n-1, d=m, x = s[i].x; i>=0 && x>=x1; --i) {
        while (s[i].x < x) a[x] = min(a[x], d++), --x;
        if (s[i].x > x1) d = min(d, abs(s[i].y - y) - 1);
    }
    for (int i=0, x=s[0].x; i<n; ++i) {
        int xc = s[i].x, yc = s[i].y;
        if (xc > x1 && xc < x2 && a[xc] >= 0 && yc >= y-a[xc] && yc <= y+a[xc]) --ans;
        while (xc > x) {
            if (x > x1 && x < x2 && a[x] >= 0) ans += min(a[x], y) + min(a[x], m-1-y) + 1;
            if (++x >= x2) return ans;
        }
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}