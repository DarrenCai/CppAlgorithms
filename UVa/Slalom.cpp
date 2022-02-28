/**
 * UVa11627
 * 障碍滑雪⽐赛
 * 暂未通过，可能是题目数据的问题
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 100100
#define S 1001000
int x[N], y[N], v[S], w, vh, n, s;

bool check(int v) {
    double a = x[0], b = a + w;
    for (int i=1; i<n; ++i) {
        double t = (y[i]-y[i-1]-0.) / v;
        a = max(a-vh*t, x[i]+0.);
        b = min(b+vh*t, x[i]+w+0.);
        if (a > b) return false;
    }
    return true;
}

void solve() {
    cin >> w >> vh >> n;
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i];
    cin >> s;
    for (int i=0; i<s; ++i) cin >> v[i];
    sort(v, v+s); s = unique(v, v+s) - v;
    int l = 0, r = s-1;
    while (l <= r) {
        int mid = (l+r)>>1;
        check(v[mid]) ? l = mid+1 : r = mid-1;
    }
    r < 0 ? cout << "IMPOSSIBLE" << endl : cout << v[r] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    short t; cin >> t;
    while (t--) solve();
    return 0;
}