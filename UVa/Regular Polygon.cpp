/**
 * UVa10824
 * 正多边形
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

#define N 2010
double t[N], e=1e-8, c1=M_PI/1.5, c2=M_PI*2, cc=c1+e; int cnt[N];

int cmp(double x, double y) {
    return abs(x-y) >= e && x<y;
}

bool check(short i, short j, short n, double d) {
    if (abs(t[i]+c2-t[j]-d) < e) return true;
    double a = t[j]+d;
    short k = lower_bound(t+j, t+n, a, cmp) - t;
    if (k == n || abs(t[k]-a) >= e) return false;
    return check(i, k, n, d);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n, kase=0;
    while (cin>>n && n) {
        for (short i=0; i<n; ++i) {
            double x, y; cin >> x >> y;
            t[i] = atan2(y, x) + M_PI;
        }
        cout << "Case " << ++kase << ':' << endl;
        if (n >= 3) {
            sort(t, t+n);
            memset(cnt, 0, sizeof(cnt));
            for (short i=0; t[i] < M_PI; ++i) for (short j=i+1; j<n; ++j) {
                double a = t[j]-t[i];
                if (a >= cc) break;
                int c = c2/a+.5;
                if (abs(a-c2/c) < e && check(i, j, n, c2/c)) ++cnt[c];
            }
        }
        for (short i=3; i<=n; ++i) if (cnt[i]) cout << i << ' ' << cnt[i] << endl;
    }
    return 0;
}