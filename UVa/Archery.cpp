
/**
 * UVa1421/LA4253
 * 箭术
 * UVa上的测试数据可能存在di=dj的情况，导致wa/re，多次提交才通过
 */

#include <iostream>
using namespace std;

#define N 5020
int d[N], l[N], r[N];

bool solve() {
    short n; cin >> r[0] >> n; ++n;
    for (short i=1; i<n; ++i) cin >> d[i] >> l[i] >> r[i];
    for (short i=0, j; i<n; ++i) {
        double a = -__DBL_MAX__, b = __DBL_MAX__, x = l[i];
        for (j=0; j<n; ++j) if (j!=i) {
            double c1 = (l[j]-x) / (d[j] - d[i]), c2 = (r[j]-x) / (d[j]-d[i]);
            a = max(a, min(c1, c2)); b = min(b, max(c1, c2));
            if (a > b) break;
        }
        if (j == n) return true;
    }
    return false;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    d[0] = 0; l[0] = 0;
    short t; cin >> t;
    while (t--) cout << (solve() ? "YES" : "NO") << endl;
    return 0;
}
