/**
 * UVa11017
 * 绿色的世界
 * 取格点的组成图形的面积为一单位。在平行四边形格点，皮克定理依然成立。
 * 套用于任意三角形格点，皮克定理则是 A = 2*i + b - 2。
 */

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int d, t, n;

long long cross(long long x1, long long y1, long long x2, long long y2) {
    return x1*y2 - x2*y1;
}

void solve() {
    long long a = 0, b = 0, x0, y0, xp, yp; cin >> x0 >> y0; xp = x0; yp = y0;
    for (int i=1; i<n; ++i) {
        long long x, y; cin >> x >> y;
        a += cross(xp-x0, yp-y0, x-x0, y-y0);
        b += 3*abs(__gcd(x-xp, y-yp)) - abs(__gcd((x-xp)<<1, y-yp)) - abs(__gcd(x-xp, (y-yp)<<1));
        xp = x; yp = y;
    }
    b += 3*abs(__gcd(x0-xp, y0-yp)) - abs(__gcd((x0-xp)<<1, y0-yp)) - abs(__gcd(x0-xp, (y0-yp)<<1));
    if (a < 0) a = -a;
    cout << ((a-b)>>1) << ' ' << (long long)(.5*a*sin(t*M_PI/180)*d*d + .5) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> d >> t >> n && (d || t || n)) solve();
    return 0;
}