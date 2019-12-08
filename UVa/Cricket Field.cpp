/**
 * UVa1312
 * 球场
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 105
#define min(a, b) (a<b ? a:b)

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    for (short k=0; k < t; ++k) {
        short p[N][2], x[N], y[N], l = 0, xq, yq, n, w, h; cin >> n >> w >> h;
        y[0] = 0; y[++n] = h;
        for (short i=1; i<n; ++i) cin >> p[i][0] >> p[i][1], y[i] = p[i][1];
        sort(y+1, y+n+1);
        for (short i=0; i<n; ++i) for (short j=i+1; j<=n; ++j) if (y[i] < y[j]) {
            short s = 0, ly = y[j] - y[i];
            for (short m=1; m<n; ++m) if (p[m][1]>y[i] && p[m][1]<y[j]) x[s++] = p[m][0];
            sort(x, x+s);
            short x1 = 0, lx = (--s >= 0 ? x[0] : w) - x1;
            if (s>=0 && w-x[s]>lx) x1 = x[s], lx = w - x1;
            for (short m=0; m<s; ++m) if (x[m+1] - x[m] > lx) x1 = x[m], lx = x[m+1] - x1;
            if ((lx = min(lx, ly)) > l) l = lx, xq = x1, yq = y[i];
        }
        if (k) cout << endl;
        cout << xq << ' ' << yq << ' ' << l << endl;
    }
    return 0;
}