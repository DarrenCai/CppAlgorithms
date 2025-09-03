/**
 * UVa1417/LA4082
 * 交通堵塞
 * Changchun 2007
 */

#include <iostream>
using namespace std;

#define N 100010
struct node {bool a, b, c, d, e, f;} s[1<<18]; int c, r1, c1, r2, c2; bool h[2][N], v[N]; char cmd[6];

void build(int o, int l, int r) {
    if (l < r) {
        int m = (l+r)>>1, lc = o<<1, rc = lc | 1;
        s[o].a = s[o].b = s[o].c = s[o].d = s[o].e = s[o].f = false;
        build(lc, l, m); build(rc, m+1, r);
    } else s[o].a = s[o].b = true, s[o].c = s[o].d = s[o].e = s[o].f = h[0][l] = h[1][l] = v[l] = false;
}

node merge(const node& x, const node& y, int m) {
    return {
        (h[0][m] && x.a && y.a) || (h[1][m] && x.c && y.d),
        (h[0][m] && x.d && y.c) || (h[1][m] && x.b && y.b),
        (h[0][m] && x.a && y.c) || (h[1][m] && x.c && y.b),
        (h[0][m] && x.d && y.a) || (h[1][m] && x.b && y.d),
        x.e || (x.a && x.b && h[0][m] && h[1][m] && y.e),
        y.f || (y.a && y.b && h[0][m] && h[1][m] && x.f)
    };
}

void op(int o, int l, int r) {
    if (l >= c1 && r <= c2) {
        if (c1 == c2) {
            s[o].c = s[o].d = s[o].e = s[o].f = v[c1];
        } else if (l < r) {
            bool a = h[0][c1], b = h[1][c1], c = v[c1], d = v[c2];
            s[o].a = a || (b && c && d); s[o].b = b || (a && c && d);
            s[o].c = (a && d) || (b && c); s[o].d = (a && c) || (b && d);
            s[o].e = c || (a && b && d); s[o].f = d || (a && b && c);
        }
    } else {
        int m = (l+r)>>1, lc = o<<1, rc = lc | 1;
        if (c1 <= m) op(lc, l, m);
        if (c2 > m) op(rc, m+1, r);
        s[o] = merge(s[lc], s[rc], m);
    }
}

void op(bool f) {
    if (c1 > c2) swap(c1, c2);
    c1 == c2 ? v[c1] = f : h[r1][c1] = f;
    op(1, 1, c);
}

node query(int o, int l, int r, int c1, int c2) {
    if (l >= c1 && r <= c2) return s[o];
    int m = (l+r)>>1, lc = o<<1, rc = lc | 1;
    if (c2 <= m) return query(lc, l, m, c1, c2);
    if (c1 > m) return query(rc, m+1, r, c1, c2);
    return merge(query(lc, l, m, c1, c2), query(rc, m+1, r, c1, c2), m);
}

bool query() {
    if (c1 > c2) swap(c1, c2), swap(r1, r2);
    node r = query(1, 1, c, c1, c2);
    if ((r1==r2 && ((r1<1 && r.a) || (r1>0 && r.b))) || (r1<r2 && r.c) || (r1>r2 && r.d)) return true;
    if (r1 == r2) return (r1<1 && r.b && query(1, 1, c, 1, c1).f && query(1, 1, c, c2, c).e)
                    || (r1>0 && r.a && query(1, 1, c, 1, c1).f && query(1, 1, c, c2, c).e);
    if (r1 < r2) return (r.a && query(1, 1, c, c2, c).e) || (r.b && query(1, 1, c, 1, c1).f)
                    || (r.d && query(1, 1, c, 1, c1).f && query(1, 1, c, c2, c).e);
    return (r.a && query(1, 1, c, 1, c1).f) || (r.b && query(1, 1, c, c2, c).e)
        || (r.c && query(1, 1, c, 1, c1).f && query(1, 1, c, c2, c).e);
}

void solve() {
    cin >> c; build(1, 1, c);
    while (cin >> cmd && cmd[0] != 'E') {
        cin >> r1 >> c1 >> r2 >> c2; --r1; --r2;
        if (cmd[0] == 'A') cout << (query() ? 'Y' : 'N') << endl;
        else op(cmd[0] == 'O');
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}