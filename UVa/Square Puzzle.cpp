/**
 * UVa10639
 * 正方形拼图
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 8
#define N 70
short m, n, f[M][M], ff[M][4][M][M], y[M][4], sx[M][4], sy[M][4]; bool vis[M];
struct polygon {
    short x[N], y[N], n;
    short area() const {
        short s = x[n-1]*y[0] - x[0]*y[n-1];
        for (short i=1; i<n; ++i) s += x[i-1]*y[i] - x[i]*y[i-1];
        return abs(s);
    }
    bool gs() {
        short xm = m<<1, ym = m<<1;
        for (short i=0; i<n; ++i) xm = min(xm, x[i]), ym = min(ym, y[i]);
        for (short i=0; i<n; ++i) if (max(x[i]-=xm, y[i]-=ym) > m) return true;
        return false;
    }
    bool same(const polygon& p) const {
        for (short i=0; i<n; ++i) if (x[i]!=p.x[i] || y[i]!=p.y[i]) return false;
        return true;
    }
    void rot(polygon& r) const {
        r.n = n; for (short i=0; i<n; ++i) r.x[i] = y[i], r.y[i] = -x[i];
    }
    bool cnt(short x0, short y0) const {
        short c = 0;
        for (short i=0; i<n; ++i) {
            short j = i+1==n ? 0 : i+1, x1 = x[i]<<2, y1 = y[i]<<2, x2 = x[j]<<2, y2 = y[j]<<2;
            if ((y1-y0)*(x2-x0)==(y2-y0)*(x1-x0) && (x1-x0)*(x2-x0)+(y1-y0)*(y2-y0)<0) return true;
            if (y0 > min(y1, y2) && y0 <= max(y1, y2) && x1 + (x2-x1)*(y0-y1)/(y2-y1) > x0) ++c;
        }
        return c&1;
    }
    void fill(short (&f)[M][M], short &ym, short &sx, short &sy) const {
        memset(f, 0, sizeof(f)); ym = M; sx = sy = 0;
        for (short i=0; i<m; ++i) for (short j=0; j<m; ++j) {
            if (cnt((i<<2)+2, (j<<2)+2)) {
                bool c1 = cnt((i<<2)+1, (j<<2)+2), c2 = cnt((i<<2)+2, (j<<2)+1),
                     c3 = cnt((i<<2)+3, (j<<2)+2), c4 = cnt((i<<2)+2, (j<<2)+3);
                f[i][j] = c1 && c2 && c3 && c4 ? 1 : (c1 && c2 ? 2 : (c2 && c3 ? 3 : (c1 && c4 ? 4 : 5)));
            } else f[i][j] = 0;
            if (i==0 && f[i][j] && ym==M) ym = j;
            if (f[i][j]) sx = max(sx, short(i+1)), sy = max(sy, short(j+1));
        }
    }
} p[M][4];
bool check(short x, short y, const short (&ff)[M][M], short ym, short sx, short sy) {
    for (short i=0; i<sx; ++i) for (short j=0; j<sy; ++j) if (ff[i][j]) {
        short x1 = x+i, y1 = y+j-ym;
        if ((x1>=m || y1<0 || y1>=m) || (f[x1][y1] && ff[i][j]+f[x1][y1] != 7)) return false;
    }
    return true;
}
void fill(short x, short y, const short (&ff)[M][M], short ym, short sx, short sy) {
    for (short i=0; i<sx; ++i) for (short j=0; j<sy; ++j) if (ff[i][j]) {
        short x1 = x+i, y1 = y+j-ym;
        f[x1][y1] += ff[i][j];
        if (f[x1][y1] == 7) f[x1][y1] = 1;
    }
}
void unfill(short x, short y, const short (&ff)[M][M], short ym, short sx, short sy) {
    for (short i=0; i<sx; ++i) for (short j=0; j<sy; ++j) if (ff[i][j]) {
        short x1 = x+i, y1 = y+j-ym;
        f[x1][y1] = f[x1][y1] == ff[i][j] ? 0 : 7-ff[i][j];
    }
}
bool dfs() {
    for (short x=0; x<m; ++x) for (short y=0; y<m; ++y) if (f[x][y] != 1) {
        for (short i=0; i<n; ++i) if (!vis[i]) {
            vis[i] = true;
            for (short j=0; j<4; ++j) if (p[i][j].n && check(x, y, ff[i][j], ::y[i][j], sx[i][j], sy[i][j])) {
                fill(x, y, ff[i][j], ::y[i][j], sx[i][j], sy[i][j]);
                if (dfs()) return true;
                unfill(x, y, ff[i][j], ::y[i][j], sx[i][j], sy[i][j]);
            }
            vis[i] = false;
        }
        return false;
    }
    return true;
}
bool solve() {
    short k, s = 0; cin >> n >> m;
    for (short i=0; i<n; ++i) {
        cin >> k; p[i][0].n = k;
        for (short j=0; j<k; ++j) cin >> p[i][0].x[j] >> p[i][0].y[j];
        s += p[i][0].area();
    }
    if (s !=  m*m<<1) return false;
    for (short i=0; i<n; ++i) if (p[i][0].gs()) return false;
    for (short i=1; i<n; ++i) for (short j=1; j<4; ++j) {
        p[i][j-1].rot(p[i][j]); p[i][j].gs();
        if (p[i][0].same(p[i][j])) {
            p[i][j].n = 0; break;
        }
    }
    for (short i=0; i<n; ++i) for (short j=0; j<4; ++j)
        if (p[i][j].n) p[i][j].fill(ff[i][j], y[i][j], sx[i][j], sy[i][j]);
    memset(vis, 0, sizeof(vis)); memset(f, 0, sizeof(f));
    return dfs();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) cout << (solve() ? "yes" : "no") << endl;
    return 0;
}
