/**
 * UVa12233/LA4488
 * 最后的战役
 * Wuhan 2009
 */

#include <iostream>
#include <map>
using namespace std;

#define INF 10000000
int d[4][3], sj, xs, ss, yj, ys, gs, cc, tt, kase = 0; char s[] = "HLMY", ans[24][4];
struct {
    int mj, ms, su, d1x, d2x, d1s, d2s, wad, ssd, ssq, ssp, q1, q2, j, q, s;
    void read() {
        cin >> mj >> ms >> su >> d1x >> d2x >> d1s >> d2s >> wad >> ssd >> ssq >> ssp >> q1 >> q2 >> j >> q >> s;
    }
} h[4];
map<int, int> r[13]; int w, k;

int dfs(int t, int j, int q, int s) {
    if (j <= 0) return -INF;
    j = min(j, h[w].mj); q = min(q, 100); s = min(s, h[w].ms);
    int u = j << 17 | q << 10 | s, d = 0, dj = 0, dq = 0;
    if (r[t].count(u)) return r[t][u];
    if (t % (5-xs) == 0) {
        int f = t / (5-xs) & 3;
        if (f == k+1) dj -= h[w].d1x, dq += h[w].q2;
        if (f == 0) dj -= h[w].d2x;
    }
    if (t % (5-ss) == 0) {
        int f = t / (5-ss) & 3;
        if (f == k+1) dj -= h[w].d1s, dq += h[w].q2;
        if (f == 0) dj -= h[w].d2s;
    }
    if (t % (5-h[w].su) == 0) {
        if (t == tt) {
            if (j > h[w].wad) d = h[w].wad;
            if (q >= h[w].ssq && (!h[w].ssp || (h[w].ssp && j > h[w].ssd))) d = max(d, h[w].ssd);
        } else {
            d = dfs(t+1, j+dj, q+h[w].q1+dq, s);
            if (s < h[w].ms) d = max(d, dfs(t+1, j+dj, q+dq, s+gs));
            if (s >= ys && j < h[w].mj) d = max(d, dfs(t+1, min(j+yj, h[w].mj)+dj, q+dq, s-ys));
            if (j > h[w].wad) d = max(d, h[w].wad + dfs(t+1, j-h[w].wad+dj, q+h[w].q1+dq, s));
            if (q >= h[w].ssq && (!h[w].ssp || (h[w].ssp && j > h[w].ssd)))
                d = max(d, h[w].ssd + dfs(t+1, h[w].ssp ? j-h[w].ssd+dj : j+dj, q-h[w].ssq+dq, s));
        }
    } else if (t < tt) d = dfs(t+1, j+dj, q+dq, s);
    return r[t][u] = d;
}

void solve() {
    h[3].read(); h[0].read(); h[1].read(); h[2].read();
    for (tt=1, cc=0; tt<=12; ++tt) {
        for (w=0; w<4; ++w) for (k=0; k<3; ++k) {
            for (int i=1; i<=tt; ++i) r[i].clear();
            d[w][k] = dfs(1, h[w].j, h[w].q, h[w].s);
        }
        for (int a=0; a<4; ++a) for (int b=0; b<4; ++b) if (a!=b) for (int c=0; c<4; ++c)
        if (c!=a && c!=b && d[a][0] + d[b][1] + d[c][2] >= sj)
            ans[cc][0] = s[a], ans[cc][1] = s[b], ans[cc][2] = s[c], ans[cc++][3] = 0;
        if (cc) break;
    }
    if (cc) {
        cout << "Case " << ++kase << ": " << tt;
        for (int i=0; i<cc; ++i) cout << ' ' << ans[i];
    } else cout << "Case " << ++kase << ": -1";
    cout << endl << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> sj >> xs >> ss >> yj >> ys >> gs && sj) solve();
    return 0;
}