/**
 * UVa1382
 * 遥远的银河
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 111
struct point {
    int x, y;
    bool operator< (const point& rhs) const {
        return y < rhs.y;
    }
} p[N];
int x[N], kase = 0; short down[N], on[N], on2[N], n;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    down[0] = on[0] = on2[0] = 0; p[0].y = x[0] = 0x80000000;
    while (cin>>n && n++) {
        for (short i=1; i<n; ++i) cin >> p[i].x >> p[i].y, x[i] = p[i].x;
        sort(x, x+n); sort(p, p+n);
        int m = unique(x, x+n) - x, ans = 0;
        for (int a=0; a<m; ++a) for (int b=a+1; b<m; ++b) {
            int mx = 0, t = 0;
            for (short i=1; i<n; ++i) {
                if (p[i].y != p[i-1].y) {
                    ++t; on[t] = on2[t] = 0;
                    down[t] = down[t-1] + on2[t-1] - on[t-1];
                }
                if (p[i].x>x[a] && p[i].x<x[b]) ++on[t];
                if (p[i].x>=x[a] && p[i].x<=x[b]) ++on2[t];
            }
            for (int i=1; i<=t; ++i) ans = max(ans, down[i]+on2[i]+mx), mx = max(mx, on[i]-down[i]);
        }
        cout << "Case " << ++kase << ": " << ans << endl;
    }
    return 0;
}