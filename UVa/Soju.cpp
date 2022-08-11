/**
 * UVa1511/LA5848
 * 烧酒
 * Asia Daejeon 2011
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 100100
struct point {
    int x, y;
    bool operator< (const point& rhs) const {
        return y < rhs.y || (y==rhs.y && x<rhs.x);
    }
} ic[N], pc[N];
int a[N], m, n;

bool cmp(int i, int j) {
    return pc[i].x-ic[0].x + pc[i].y-ic[0].y < pc[j].x-ic[0].x + pc[j].y-ic[0].y;
}

int solve() {
    cin >> n; for (int i=0; i<n; ++i) cin >> ic[i].x >> ic[i].y;
    cin >> m; for (int i=0; i<m; ++i) cin >> pc[i].x >> pc[i].y;
    sort(ic, ic+n); sort(pc, pc+m);
    int ans = pc[0].x-ic[0].x + abs(pc[0].y-ic[0].y), d = 0, t = 0, u = m;
    for (int i=0; i<m; ++i) {
        if (i>0 && pc[i-1].y==pc[i].y) continue;
        if (pc[i].y <= ic[0].y) {
            int dis = pc[i].x - ic[0].x + ic[0].y - pc[i].y;
            if (!d || dis<d) d = dis;
        } else {
            a[t++] = i;
            if (u == m) u = i;
        }
    }
    if (d) ans = min(ans, d);
    if (t) {
        sort(a, a+t, cmp);
        ans = min(ans, pc[a[0]].x - ic[0].x + pc[a[0]].y - ic[0].y);
    }
    for (int i=1, h=0; i<n; ++i) {
        if (d) d += ic[i-1].x - ic[i].x + ic[i].y - ic[i-1].y;
        while (u<m && pc[u].y<=ic[i].y) {
            int dis = pc[u].x - ic[i].x + ic[i].y - pc[u].y;
            if (!d || dis<d) d = dis;
            ++u;
        }
        if (d) ans = min(ans, d);
        while (h<t && a[h]<u) ++h;
        if (h<t) ans = min(ans, pc[a[h]].x - ic[i].x + pc[a[h]].y - ic[i].y);
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