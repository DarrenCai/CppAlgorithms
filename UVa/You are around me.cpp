/**
 * UVa12121/LA4062
 * Asia Dhaka 2007
 * 最邻近点对问题(Closest-Pair Problem)
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;

#define N 15010
#define dis(a, b) sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y))
int a[N], n, kase = 0; double p = M_PI / 180, d, e, t;
struct point {
    double x, y;
    bool operator< (const point& rhs) const {
        return x < rhs.x;
    }
} s[N];

bool cmp(int i, int j) {
    return s[i].y < s[j].y;
}

void closest_dis(int l, int r) {
    if (r-l == 1) {
        d = min(d, dis(s[l], s[r]));
    } else if (r-l > 1) {
        int m = (l+r)>>1, c = 0;
        closest_dis(l, m);
        closest_dis(m+1, r);
        for (int i=m; i>=l; --i) {
            if (s[m].x-s[i].x >= d) break;
            a[c++] = i;
        }
        for (int i=m+1; i<=r; ++i) {
            if (s[i].x-s[m].x >= d) break;
            a[c++] = i;
        }
        sort(a, a+c, cmp);
        for (int i=0; i<c; ++i) for (int j=i+1, k=i+7; j<k; ++j) {
            if (j>=c || s[a[j]].y>=s[a[i]].y+d) break;
            d = min(d, dis(s[a[i]], s[a[j]]));
        }
    }
}

double solve() {
    t *= p; e = sqrt(1 - e*e);
    double co = cos(t), si = sin(t);
    for (int i=0; i<n; ++i) {
        double a, b; cin >> a >> b;
        s[i].x = e * (a*co + b*si);
        s[i].y = b*co - a*si;
    }
    if (e == 0) return 0;
    d = __DBL_MAX__;
    sort(s, s+n);
    closest_dis(0, n-1);
    return M_PI * d * d / 4 / e;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(6);
    while (cin>>n>>e>>t && n) cout << "Case " << ++kase << ':' << endl << solve() << endl;
    return 0;
}