/**
 * UVa12170
 * 轻松爬山
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define abs(x) ((x)>=0 ? (x):-(x))
#define N 110
long long h[N], q[N*N<<1], x[N*N<<1], f[N][N*N<<1]; const long long INF = 1e12;

void solve() {
    int n, c=0; long long d; cin >> n >> d;
    for (int i=0; i<n; ++i) {
        cin >> h[i];
        int m = max(i, n-1-i);
        for (int j=-m; j<=m; ++j) x[c++] = d*j+h[i];
    }
    if (abs(h[n-1]-h[0]) > d*(n-1)) {
        cout << "impossible" << endl;
        return;
    }
    if (n == 2) {
        cout << 0 << endl;
        return;
    }
    sort(x, x+c);
    c = unique(x, x+c) - x;
    for (int i=0; i<c; ++i) f[1][i] = abs(x[i]-h[0]) > d ? INF : abs(h[1]-x[i]);
    for (int i=2; i<n; ++i) {
        int head=0, tail=-1, last;
        for (last=0; last < c && x[last] <= x[0]+d; ++last) {
            while (tail >= head && f[i-1][q[tail]] > f[i-1][last]) --tail;
            q[++tail] = last;
        }
        f[i][0] = abs(x[0]-h[i]) + f[i-1][q[head]];
        for (int j=1; j<c; ++j) {
            for (; last < c && x[last] <= x[j]+d; ++last) {
                while (tail >= head && f[i-1][q[tail]] > f[i-1][last]) --tail;
                q[++tail] = last;
            }
            while (head <= tail && x[q[head]] < x[j]-d) ++head;
            f[i][j] = abs(x[j]-h[i]) + f[i-1][q[head]];
        }
    }
    for (int i=0; i<c; ++i) if (x[i] == h[n-1]) {
        cout << f[n-1][i] << endl;
        return;
    }
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}