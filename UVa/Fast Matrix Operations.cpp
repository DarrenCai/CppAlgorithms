/**
 * UVa11992
 * 快速矩阵操作
 */

#include <iostream>
using namespace std;

#define N 21
#define INF 1000000000
struct node {int s, x, y; node(int s, int x, int y): s(s), x(x), y(y) {}} p(0, 0, 0);
int s[N][1<<N], x[N][1<<N], y[N][1<<N], a[N][1<<N], e[N][1<<N], r, c, m, t, x1, y1, x2, y2, v;

node query(int i, int o, int l, int r, int t = 0) {
    if (e[i][o] >= 0) {
        t += a[i][o] + e[i][o];
        return node(t * (min(r, y2) - max(l, y1) + 1), t, t);
    }
    if (l>=y1 && r<=y2) return node(s[i][o] + t*(r-l+1), t + x[i][o], t + y[i][o]);
    int ss = 0, sx = INF, sy = 0, m = (l+r)>>1, lc = o<<1, rc = lc+1; t += a[i][o];
    if (y1 <= m) p = query(i, lc, l, m, t), ss += p.s, sx = min(sx, p.x), sy = max(sy, p.y);
    if (y2 > m) p = query(i, rc, m+1, r, t), ss += p.s, sx = min(sx, p.x), sy = max(sy, p.y);
    return node(ss, sx, sy);
}

void update(int o, int l, int r) {
    for (int i=x1; i<=x2; ++i) {
        if (e[i][o] >= 0) {
            int v = a[i][o] + e[i][o]; s[i][o] = v * (r-l+1); x[i][o] = v; y[i][o] = v;
        } else if (l < r) {
            int lc = o<<1, rc = lc+1;
            s[i][o] = s[i][lc] + s[i][rc]; x[i][o] = min(x[i][lc], x[i][rc]); y[i][o] = max(y[i][lc], y[i][rc]);
            s[i][o] += a[i][o]*(r-l+1); x[i][o] += a[i][o]; y[i][o] += a[i][o];
        } else s[i][o] = a[i][o], x[i][o] = a[i][o], y[i][o] = a[i][o];
    }
}

void op(int o, int l, int r) {
    if (l>=y1 && r<=y2) {
        for (int i=x1; i<=x2; ++i) t == 1 ? a[i][o] += v : (e[i][o] = v, a[i][o] = 0);
    } else {
        int m = (l+r)>>1, lc = o<<1, rc = lc+1;
        for (int i=x1; i<=x2; ++i) {
            if (e[i][o] >= 0) e[i][lc] = e[i][rc] = e[i][o], a[i][lc] = a[i][rc] = 0, e[i][o] = -1;
            if (a[i][o]) a[i][lc] += a[i][o], a[i][rc] += a[i][o], a[i][o] = 0;
        }
        y1 <= m ? op(lc, l, m) : update(lc, l, m);
        y2 > m ? op(rc, m+1, r) : update(rc, m+1, r);
    }
    update(o, l, r);
}

void build(int o, int l, int r) {
    for (int i=1; i<=::r; ++i) s[i][o] = x[i][o] = y[i][o] = a[i][o] = 0, e[i][o] = -1;
    if (l < r) {
        int m = (l+r)>>1, lc = o<<1, rc = lc+1;
        build(lc, l, m); build(rc, m+1, r);
    }
}

void solve() {
    build(1, 1, c);
    while (m--) {
        cin >> t >> x1 >> y1 >> x2 >> y2;
        if (t == 3) {
            int ss = 0, sx = INF, sy = 0;
            for (int i=x1; i<=x2; ++i) p = query(i, 1, 1, c), ss += p.s, sx = min(sx, p.x), sy = max(sy, p.y);
            cout << ss << ' ' << sx << ' ' << sy << endl;
        } else cin >> v, op(1, 1, c);
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> r >> c >> m) solve();
    return 0;
}