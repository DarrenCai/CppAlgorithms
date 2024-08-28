/**
 * UVa1666/LA6330
 * 最短路线
 * Jinhua 2012
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;

#define M 60
#define N 15000
struct point {
    int x, y;
    bool operator< (const point& rhs) const {
        return x < rhs.x || (x==rhs.x && y<rhs.y);
    }
} p[N], p1, p2, t;
struct {int u, d;} q[N<<14]; map<point, int> id;
enum s {in, bo, ou}; int b[M][4], g[N][4], d[N<<2], sx[M<<1], sy[M<<1], cx, cy, m, n; bool c[N][6];

s judge(const point& pt, const int (&rec)[4]) {
    if (pt.x < min(rec[0], rec[2]) || pt.x > max(rec[0], rec[2]) ||
        pt.y < min(rec[1], rec[3]) || pt.y > max(rec[1], rec[3])) return ou;
    if (pt.x > min(rec[0], rec[2]) && pt.x < max(rec[0], rec[2]) &&
        pt.y > min(rec[1], rec[3]) && pt.y < max(rec[1], rec[3])) return in;
    return bo;
}

s judge(double x, double y, const int (&rec)[4]) {
    if (x < min(rec[0], rec[2]) || x > max(rec[0], rec[2]) ||
        y < min(rec[1], rec[3]) || y > max(rec[1], rec[3])) return ou;
    if (x > min(rec[0], rec[2]) && x < max(rec[0], rec[2]) &&
        y > min(rec[1], rec[3]) && y < max(rec[1], rec[3])) return in;
    return bo;
}

bool check(const point& pt, bool (&c)[6]) {
    double x = pt.x + .5, y = pt.y + .5; c[0] = c[1] = c[2] = c[3] = true;
    for (short i=0; i<m; ++i) if (judge(x, y, b[i]) == in) { c[0] = false; break; }
    x = pt.x - .5; y = pt.y + .5;
    for (short i=0; i<m; ++i) if (judge(x, y, b[i]) == in) { c[1] = false; break; }
    x = pt.x + .5; y = pt.y - .5;
    for (short i=0; i<m; ++i) if (judge(x, y, b[i]) == in) { c[2] = false; break; }
    x = pt.x - .5; y = pt.y - .5;
    for (short i=0; i<m; ++i) if (judge(x, y, b[i]) == in) { c[3] = false; break; }
    c[4] = (c[0] && c[2]) || (c[1] && c[3]);
    c[5] = (c[0] && c[1]) || (c[2] && c[3]);
    return c[0] || c[1] || c[2] || c[3];
}

bool check(int u, short d1, short d2) {
    if (d1+d2 == 3) return true;
    if (d1==d2) return d1==0 || d1==3 ?
        (c[u][0] && c[u][2]) || (c[u][1] && c[u][3]) : (c[u][0] && c[u][1]) || (c[u][2] && c[u][3]);
    if ((d1==0 && d2==1) || (d1==1 && d2==0) || (d1==3 && d2==2) || (d1==2 && d2==3)) return c[u][1] || c[u][2];
    if ((d1==0 && d2==2) || (d1==2 && d2==0) || (d1==3 && d2==1) || (d1==1 && d2==3)) return c[u][0] || c[u][3];
}

void build(int u = 0) {
    g[u][0] = g[u][1] = g[u][2] = g[u][3] = 0;
    int k = lower_bound(sy, sy+cy, p[u].y+1) - sy, v;
    if (k < cy && (c[u][0] || c[u][1])) {
        t.x = p[u].x; t.y = sy[k];
        if (!id.count(t) && check(t, c[n]) && (c[n][2] || c[n][3])) {
            p[g[u][3] = id[t] = n] = t; build(n++);
        } else if (id.count(t) && (v=id[t]) && (c[v][2] || c[v][3])) g[u][3] = v;
    }
    k = lower_bound(sy, sy+cy, p[u].y) - sy;
    if (--k >= 0 && (c[u][2] || c[u][3])) {
        t.x = p[u].x; t.y = sy[k];
        if (!id.count(t) && check(t, c[n]) && (c[n][0] || c[n][1])) {
            p[g[u][0] = id[t] = n] = t; build(n++);
        } else if (id.count(t) && (v=id[t]) && (c[v][0] || c[v][1])) g[u][0] = v;
    }
    k = lower_bound(sx, sx+cx, p[u].x+1) - sx;
    if (k < cx && (c[u][0] || c[u][2])) {
        t.y = p[u].y; t.x = sx[k];
        if (!id.count(t) && check(t, c[n]) && (c[n][1] || c[n][3])) {
            p[g[u][2] = id[t] = n] = t; build(n++);
        } else if (id.count(t) && (v=id[t]) && (c[v][1] || c[v][3])) g[u][2] = v;
    }
    k = lower_bound(sx, sx+cx, p[u].x) - sx;
    if (--k >= 0 && (c[u][1] || c[u][3])) {
        t.y = p[u].y; t.x = sx[k];
        if (!id.count(t) && check(t, c[n]) && (c[n][0] || c[n][2])) {
            p[g[u][1] = id[t] = n] = t; build(n++);
        } else if (id.count(t) && (v=id[t]) && (c[v][0] || c[v][2])) g[u][1] = v;
    }
}

void solve() {
    if (p1.x!=p2.x || p1.y!=p2.y) {
        if (m == 0) {
            cout << (p1.x==p2.x || p1.y==p2.y ? 0 : 1) << endl;
            return;
        }
        for (short i=0; i<m; ++i) {
            if (judge(p1, b[i]) == in) {
                cout << (judge(p2, b[i]) == ou ? -1 : (p1.x==p2.x || p1.y==p2.y ? 0 : 1)) << endl;
                return;
            }
            if (judge(p2, b[i]) == in) {
                cout << (judge(p1, b[i]) == ou ? -1 : (p1.x==p2.x || p1.y==p2.y ? 0 : 1)) << endl;
                return;
            }
        }
        if (!check(p1, c[0])) {
            cout << -1 << endl;
            return;
        }
        id.clear(); p[id[p1] = 0] = p1;
        if (!check(p2, c[1])) {
            cout << -1 << endl;
            return;
        }
        p[id[p2] = 1] = p2; cx = cy = 0; n = 2;
        sx[cx++] = p1.x; sx[cx++] = p2.x; sy[cy++] = p1.y; sy[cy++] = p2.y;
        for (short i=0; i<m; ++i) sx[cx++] = b[i][0], sx[cx++] = b[i][2], sy[cy++] = b[i][1], sy[cy++] = b[i][3];
        sort(sx, sx+cx); sort(sy, sy+cy); cx = unique(sx, sx+cx)-sx; cy = unique(sy, sy+cy)-sy; build();
        int head = 0, tail = 0, ans = -1;
        memset(d, -1, sizeof(d));
        for (int i=0, u; i<4; ++i) if (g[0][i] > 0) q[tail].d = d[u = 4*g[0][i]+i] = 0, q[tail++].u = u;
        while (head < tail) {
            int u = q[head].u, dd = q[head++].d, d1 = u&3;
            if (dd == d[u]) {
                u >>= 2;
                for (int i=0, v; i<4; ++i) if ((v = g[u][i]) > 0 && check(u, d1, i)) {
                    int w = dd + (d1!=i), vv = 4*v+i;
                    if (d[vv]<0 || d[vv]>w) q[tail].d = d[vv] = w, q[tail++].u = vv;
                    if (v==1) ans = ans<0 ? d[vv] : min(ans, d[vv]);
                }
            }
        }
        cout << ans << endl;
    } else cout << 0 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>p1.x>>p1.y>>p2.x>>p2.y && (p1.x || p1.y || p2.x || p2.y)) {
        cin >> m;
        for (short i=0; i<m; ++i) cin >> b[i][0] >> b[i][1] >> b[i][2] >> b[i][3];
        solve();
    }
    return 0;
}