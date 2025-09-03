/**
 * UVa11607
 * 切蛋糕
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define M 10000
#define N 1510
#define B 8
int x[N], y[N], u[N], v[N], x1, y1, x2, y2, dx1, dy1, dx2, dy2, vx, vy, a, b, m, n, p, r, kase = 0;

int cross(int x1, int y1, int x2, int y2) {
    return x1*y2 - x2*y1;
}

struct {
    int b[N], bx1, by1, bx2, by2, by4, c;
    void add(int i) {
        b[c++] = i;
        if (c == 1) bx1 = bx2 =x[i], by1 = by2 = y[i];
        else bx1 = min(bx1, x[i]), bx2 = max(bx2, x[i]), by1 = min(by1, y[i]), by2 = max(by2, y[i]);
    }
    void query() {
        int cc = cross(vx, vy, bx1 - x1, by1 - y1); bool e = cc < 0, f = cc == 0, g = cc > 0;
        cc = cross(vx, vy, bx2 - x1, by1 - y1); e = e || cc < 0; f = f || cc == 0; g = g || cc > 0;
        cc = cross(vx, vy, bx1 - x1, by2 - y1); e = e || cc < 0; f = f || cc == 0; g = g || cc > 0;
        cc = cross(vx, vy, bx2 - x1, by2 - y1); e = e || cc < 0; f = f || cc == 0; g = g || cc > 0;
        if (f || (e && g)) {
            for (int i=0; i<c; ++i) {
                cc = cross(vx, vy, x[b[i]]-x1, y[b[i]]-y1);
                if (cc > 0) ++p;
                else if (cc == 0) ++r;
            }
        } else if (g) p += c;
    }
} s[B][B];

void query() {
    x1 = (x1 + dx1) % M; y1 = (y1 + dy1) % M; x2 = (x2 + dx2) % M; y2 = (y2 + dy2) % M;
    if (x1 == x2 && y1 == y2) y2 = (y1 + 1) % M;
    p = 0; r = 0; vx = x2 - x1; vy = y2 - y1;
    for (int i=0; i<B; ++i) for (int j=0; j<B; ++j) s[i][j].query();
    cout << min(p, n-r-p) << ' ' << max(p, n-r-p) << ' ' << r << endl;
}

void solve() {
    cin >> n;
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i], u[i] = x[i], v[i] = x[i];
    sort(u, u+n); sort(v, v+n); a = unique(u, u+n) - u; b = unique(v, v+n) - v;
    for (int i=0; i<B; ++i) for (int j=0; j<B; ++j) s[i][j].c = 0;
    for (int i=0, j=(a+B-1)/B, k=(b+B-1)/B; i<n; ++i)
        s[(lower_bound(u, u+a, x[i]) - u) / j][(lower_bound(v, v+b, y[i]) - v) / k].add(i);
    cout << "Case #" << ++kase << ':' << endl;
    cin >> m >> x1 >> y1 >> x2 >> y2 >> dx1 >> dy1 >> dx2 >> dy2;
    while (m--) query();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}