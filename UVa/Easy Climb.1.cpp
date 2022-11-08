/**
 * UVa12170/LA4290
 * 轻松爬山
 * NWERC 2008
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 105
long long f[2][N*N<<1], a[N*N<<1], h[N], b[N], d, x, y; int q[N*N<<1];

void solve() {
    int n, m = 0;
    cin >> n >> d >> h[0]; x = y = h[0];
    for (int i=1; i<n; ++i) cin >> h[i], x = min(x, h[i]), y = max(y, h[i]);
    if (abs(h[n-1] - h[0]) > (n-1) * d) {
        cout << "impossible" << endl;
        return;
    } else if (n == 2) {
        cout << 0 << endl;
        return;
    }
    for (int i=0; i<n; ++i) {
        for (int j=0, v = h[i]-d; j<n; ++j) {
            if ((v += d) > y) break;
            a[m++] = v;
        }
        for (int j=1, v = h[i]; j<n; ++j) {
            if ((v -= d) < x) break;
            a[m++] = v;
        }
    }
    sort(a, a+m);
    m = unique(a, a+m) - a;
    int k1 = lower_bound(a, a+m, h[0]-d) - a, k2 = lower_bound(a, a+m, h[0]+d) - a;
    if (k2 == m || a[k2] > h[0]+d) --k2;
    for (int i=k1; i<=k2; ++i) f[1][i] = abs(a[i]-h[1]);
    for (int i=2; i+1<n; ++i) {
        int x = lower_bound(a, a+m, a[k1]-d) - a, y = lower_bound(a, a+m, a[k2]+d) - a;
        if (y == m || a[y] > a[k2]+d) --y;
        int head = 0, tail = 1; q[0] = k1;
        for (int j=x; j<=y; ++j) {
            while (head<tail && a[q[head]]<a[j]-d) ++head;
            int k = q[tail-1];
            while (++k<=k2 && a[k]<=a[j]+d) {
                if (a[k]<a[j]-d) continue;
                while (head<tail && f[~i&1][k]<=f[~i&1][q[tail-1]]) --tail;
                q[tail++] = k;
            }
            f[i&1][j] = f[~i&1][q[head]] + abs(a[j] - h[i]);
        }
        k1 = x; k2 = y;
    }
    long long ans = y*(n-2);
    for (int i=k1; i<=k2; ++i) if (abs(a[i]-h[n-1]) <= d) ans = min(ans, f[n&1][i]);
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) solve();
    return 0;
}