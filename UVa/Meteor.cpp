/**
 * UVa1398
 * 流星
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 100100
struct event {
    double t; bool f;
    bool operator< (const event& rhs) const {
        return t<rhs.t || (t==rhs.t && f);
    }
} s[N<<1];
int w, h, n, m, cnt;

void update(int x, int a, int w, double& l, double& r) {
    if (a == 0) {
        if (x<=0 || x>=w) r = l-1;
    } else if (a > 0) {
        l = max(l, -(double)x/a);
        r = min(r, (double)(w-x)/a);
    } else {
        l = max(l, (double)(w-x)/a);
        r = min(r, -(double)x/a);
    }
}

void add() {
    int x, y, a, b;
    cin >> x >> y >> a >> b;
    double l = 0., r = 1e9;
    update(x, a, w, l, r); update(y, b, h, l, r);
    if (l < r) {
        s[m].t = l; s[m++].f = false;
        s[m].t = r; s[m++].f = true;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> w >> h >> n; cnt = m = 0;
        for (int i=0; i<n; ++i) add();
        sort(s, s+m);
        int cur = 0;
        for (int i=0; i<m; ++i) s[i].f ? --cur : cnt = max(cnt, ++cur);
        cout << cnt << endl;
    }
    return 0;
}