/**
 * UVa1432/LA4356
 * 火势控制系统
 * Hangzhou 2008
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;

#define N 5020
int c[N], n, k, kase = 0;
struct angle {
    int x, y; double v;
    angle() {}
    angle(int x, int y):x(x), y(y) {
        v = atan2(y, x) / 2.;
        if (v < 0.) v += M_PI;
    }
    int sector() const {
        if (x>0 && y>=0) return 0;
        if (y>0 && x<=0) return 1;
        if (x<0 && y<=0) return 2;
        return 3;
    }
    bool operator< (const angle& rhs) const {
        int s1 = sector(), s2 = rhs.sector();
        if (s1 != s2) return s1 < s2;
        return rhs.x*y < x*rhs.y;
    }
    bool operator== (const angle& rhs) const {
        int s1 = sector(), s2 = rhs.sector();
        if (s1 != s2) return false;
        return rhs.x*y == x*rhs.y;
    }
} a[N];
struct point {
    int x, y;
    bool operator< (const point& rhs) const {
        int r1 = x*x + y*y, r2 = rhs.x*rhs.x + rhs.y*rhs.y;
        if (r1 != r2) return r1 < r2;
        angle a1, a2; a1.x = x; a1.y = y; a2.x = rhs.x; a2.y = rhs.y;
        return a1 < a2;
    }
} p[N];

double solve() {
    for (int i=0; i<n; ++i) {
        cin >> p[i].x >> p[i].y;
        a[i] = angle(p[i].x, p[i].y); c[i] = 0;
    }
    sort(p, p+n); sort(a, a+n);
    int m = unique(a, a+n) - a, cc = 0, t = 2*m; double ans = M_PI * (p[n-1].x * p[n-1].x + p[n-1].y * p[n-1].y);
    for (int i=0; i<n; ++i) {
        angle ang; ang.x = p[i].x; ang.y = p[i].y;
        ++c[lower_bound(a, a+m, ang) - a]; ++cc;
        if (cc < k) continue;
        for (int l=0, r=0, s=0, r2 = p[i].x * p[i].x + p[i].y * p[i].y; r<t; ++r) {
            s += c[r>=m ? r-m : r];
            if (s >= k) {
                while (l<r && s-c[l>=m ? l-m : l]>=k) {
                    s -= c[l>=m ? l-m : l];
                    ++l;
                }
                if (l == r) return 0.;
                if (r-l >= m) continue;
                double g = a[r>=m ? r-m : r].v - a[l>=m ? l-m : l].v;
                if (g < 0) g += M_PI;
                ans = min(ans, g * r2);
                double tc = ans;
            }
        }
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(2);
    while (cin>>n>>k && n) cout << "Case #" << ++kase << ": " << solve() << endl;
    return 0;
}