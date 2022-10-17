/**
 * UVa1467
 * 安装服务
 * Asia Daejeon 2010
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 520
struct node {
    int s, d;
    bool operator< (const node& rhs) const {
        return d<rhs.d || (d==rhs.d && s<rhs.s); // 其实 d<rhs.d 即可
    }
} b[N];

int solve() {
    short n; cin >> n;
    for (short i=0; i<n; ++i) cin >> b[i].s >> b[i].d;
    sort(b, b+n);
    int s = 0, px = 0, py = 0; short x, y;
    for (short i=0; i<n; ++i) {
        s += b[i].s;
        int v = s - b[i].d;
        if (v > 0) {
            if (px < 1) {
                px = v; x = i;
            } else if (v >= px) {
                if (px > py) y = x;
                py = px; px = v; x = i;
            } else if (v >= py) {
                py = v; y = i;
            }
        }
    }
    int ans = px + py;
    if (py > 0) {
        int pr = px;
        if (y > x) {
            int t = y; y = x; x = t; pr = py;
        }
        for (int i=n-1, pp=0; i>=x; s -= b[i--].s) {
            py = pp;
            for (int j=0, ss = 0; j<y; ++j) {
                ans = min(ans, s - b[j].d + max(py, px - b[j].s));
                py = max(py, (ss += b[j].s) - b[j].d);
            }
            ans = min(ans, s - b[y].d + max(py, pr - b[y].s));
            pp = max(pp, s - b[i].d);
        }
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}