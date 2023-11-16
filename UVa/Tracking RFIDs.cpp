/**
 * UVa1517/LA5908
 * NWERC 2011
 */

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

#define M 12
#define N 10002
int se[N<<1][N<<1], c[N<<1], wa[M], ax[1681], ay[1681], bx[M], by[M], ex[M], ey[M], mx, s, r, w, p, x, y;

bool intersect(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3, long long x4, long long y4) {
    if (max(x1, x2) < min(x3, x4) || max(x3, x4) < min(x1, x2) || max(y1, y2) < min(y3, y4) || max(y3, y4) < min(y1, y2))
        return false;
    if (((x1 - x3)*(y4 - y3) - (y1 - y3)*(x4 - x3)) * ((x2 - x3)*(y4 - y3) - (y2 - y3)*(x4 - x3)) > 0 ||
        ((x3 - x1)*(y2 - y1) - (y3 - y1)*(x2 - x1)) * ((x4 - x1)*(y2 - y1) - (y4 - y1)*(x2 - x1)) > 0)
        return false;
    return true;
}

bool check(int x1, int y1) {
    int c = 0, d = (x-x1)*(x-x1) + (y-y1)*(y-y1);
    for (int i=0; i<w; ++i) if (intersect(x, y, x1, y1, bx[i], by[i], ex[i], ey[i])) ++c;
    c = max(0, r-c);
    return d <= c*c;
}

void solve() {
    cin >> s >> r >> w >> p;
    memset(c, 0, sizeof(c));
    while (s--) cin >> x >> y, se[x+N][c[x+N]++] = y+N;
    for (int i=mx; i>=0; --i) sort(se[i], se[i]+c[i]);
    for (int i=0; i<w; ++i) cin >> bx[i] >> by[i] >> ex[i] >> ey[i], bx[i] += N, by[i] += N, ex[i] += N, ey[i] += N;
    for (int i=0; i<p; ++i) {
        cin >> x >> y; x += N; y += N; s = 0;
        for (int x0=max(0, x-r), x1=min(mx, x+r); x0<=x1; ++x0) {
            int d = sqrt(r*r-(x-x0)*(x-x0)+.5), y0 = max(0, y-d);
            int j = lower_bound(se[x0], se[x0]+c[x0], y0) - se[x0];
            for (int y1 = min(mx, y+d); j < c[x0] && se[x0][j] <= y1; ++j)
                if (check(x0, se[x0][j])) ax[s] = x0-N, ay[s++] = se[x0][j]-N;
        }
        cout << s;
        for (int j=0; j<s; ++j) cout << " (" << ax[j] << ',' << ay[j] << ')';
        cout << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t; mx = 2*N-1;
    while (t--) solve();
    return 0;
}