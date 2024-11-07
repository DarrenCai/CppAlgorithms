/**
 * UVa11297
 * 人口普查
 */

#include <iostream>
using namespace std;

#define INF 2000000000
#define N 1024
struct node {int x, y;} t; int a[N>>1][N>>1], n;
struct st {
    node v[N];
    void build(int i, int o, int l, int r) {
        if (l == r) {
            v[o].x = v[o].y = a[i][l];
        } else {
            int m = (l+r)>>1, lc = o<<1, rc = lc+1;
            build(i, lc, l, m); build(i, rc, m+1, r);
            v[o].x = min(v[lc].x, v[rc].x); v[o].y = max(v[lc].y, v[rc].y);
        }
    }
    void build(const st& ls, const st& rs, int o, int l, int r) {
        if (l == r) {
            v[o].x = min(ls.v[o].x, rs.v[o].x); v[o].y = max(ls.v[o].y, rs.v[o].y);
        } else {
            int m = (l+r)>>1, lc = o<<1, rc = lc+1;
            build(ls, rs, lc, l, m); build(ls, rs, rc, m+1, r);
            v[o].x = min(v[lc].x, v[rc].x); v[o].y = max(v[lc].y, v[rc].y);
        }
    }
    void upd(const st& ls, const st& rs, int o, int l, int r, int y) {
        if (l == r) {
            v[o].x = min(ls.v[o].x, rs.v[o].x); v[o].y = max(ls.v[o].y, rs.v[o].y);
        } else {
            int m = (l+r)>>1, lc = o<<1, rc = lc+1;
            y <= m ? upd(ls, rs, lc, l, m, y) : upd(ls, rs, rc, m+1, r, y);
            v[o].x = min(v[lc].x, v[rc].x); v[o].y = max(v[lc].y, v[rc].y);
        }
    }
    void set(int o, int l, int r, int y, int w) {
        if (l == r) {
            v[o].x = v[o].y = w;
        } else {
            int m = (l+r)>>1, lc = o<<1, rc = lc+1;
            y <= m ? set(lc, l, m, y, w) : set(rc, m+1, r, y, w);
            v[o].x = min(v[lc].x, v[rc].x); v[o].y = max(v[lc].y, v[rc].y);
        }
    }
    node query(int o, int l, int r, int y1, int y2) {
        if (l >= y1 && r <= y2) return v[o];
        int m = (l+r)>>1, lc = o<<1, rc = lc+1, x = INF, y = -INF;
        if (y1 <= m) t = query(lc, l, m, y1, y2), x = min(x, t.x), y = max(y, t.y);
        if (y2 > m) t = query(rc, m+1, r, y1, y2), x = min(x, t.x), y = max(y, t.y);
        return {x, y};
    }
} row[N];

void build(int o, int l, int r) {
    if (l == r) return row[o].build(l, 1, 1, n);
    int m = (l+r)>>1, lc = o<<1, rc = lc+1;
    build(lc, l, m); build(rc, m+1, r); row[o].build(row[lc], row[rc], 1, 1, n);
}

void set(int o, int l, int r, int x, int y, int w) {
    if (l == r) return row[o].set(1, 1, n, y, w);
    int m = (l+r)>>1, lc = o<<1, rc = lc+1;
    x <= m ? set(lc, l, m, x, y, w) : set(rc, m+1, r, x, y, w);
    row[o].upd(row[lc], row[rc], 1, 1, n, y);
}

node query(int o, int l, int r, int x1, int y1, int x2, int y2) {
    if (l >= x1 && r <= x2) return row[o].query(1, 1, n, y1, y2);
    int m = (l+r)>>1, lc = o<<1, rc = lc+1, x = INF, y = -INF;
    if (x1 <= m) t = query(lc, l, m, x1, y1, x2, y2), x = min(x, t.x), y = max(y, t.y);
    if (x2 > m) t = query(rc, m+1, r, x1, y1, x2, y2), x = min(x, t.x), y = max(y, t.y);
    return {x, y};
}

void set() {
    int x, y, w; cin >> x >> y >> w;
    set(1, 1, n, x, y, w);
}

void query() {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    t = query(1, 1, n, x1, y1, x2, y2);
    cout << t.y << ' ' << t.x << endl;
}

void solve() {
    cin >> n;
    for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) cin >> a[i][j];
    build(1, 1, n);
    int q; cin >> q;
    while (q--) {
        char c; cin >> c;
        c == 'c' ? set() : query();
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}