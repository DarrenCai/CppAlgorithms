/**
 * UVa1321/LA2925
 * CERC 2003
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define L 19
long long d[4][24][4][24][L], a[4][24][4][24][31], e[2][4][24]; bool f[4][24][L];
int c[][2] = {{2, 3}, {6, 3}, {6, 5}, {6, 2}, {6, 4}, {2, 4}}, w[7], x1, y1, x2, y2;

struct node {
    int y, s, x; long long d;
    bool operator< (const node &rhs) const {
        return d > rhs.d;
    }
} t;

int encode(int t, int f) {
    --t;
    return (t<<2) + (f == c[t][0] ? 0 : (f == c[t][1] ? 1 : (f == 7-c[t][0] ? 2 : 3)));
}

void decode(int s, int &t, int &f) {
    t = s>>2; f = s&3; f = f < 2 ? c[t++][f] : 7-c[t++][f-2];
}

void roll(int s, int d, int &t, int &f) {
    int t0, f0; decode(s, t0, f0); int (&e)[2] = c[t0-1];
    if (d == 0) t = f0, f = 7-t0;
    else if (d == 1) t = 7-f0, f = t0;
    else if (d == 2) t = f0 == e[0] ? 7-e[1] : (f0 == e[1] ? e[0] : (f0 == 7-e[0] ? e[1] : 7-e[0])), f = f0;
    else t = f0 == e[0] ? e[1] : (f0 == e[1] ? 7-e[0] : (f0 == 7-e[0] ? 7-e[1] : e[0])), f = f0;
}

long long solve() {
    for (int i=1; i<7; ++i) cin >> w[i];
    cin >> x1 >> y1 >> x2 >> y2; x2 -= x1; --y1; --y2;
    priority_queue<node> q; memset(d, 1, sizeof(d));
    for (int i=0; i<4; ++i) for (int j=0; j<24; ++j) {
        long long (&r)[4][24][L] = d[i][j]; q.push((node){i, j, 0, r[i][j][0] = 0}); memset(f, 0, sizeof(f));
        while (!q.empty()) {
            t = q.top(); q.pop(); int y = t.y, s = t.s, x = t.x > (L>>1) ? t.x-L : t.x; long long d = t.d;
            if (f[y][t.x][s]) continue;
            f[y][t.x][s] = true;
            for (int k=0; k<4; ++k) {
                int u = k<2 ? (k ? y-1 : y+1) : y, v = k<2 ? x : (k>2 ? x+1 : x-1), t, f, g; roll(s, k, t, f);
                if (u<0 || u>3 || abs(v) > (L>>1)) continue;
                if (v < 0) v += L;
                if (d + w[t] < r[u][g = encode(t, f)][v]) q.push((node){u, g, v, r[u][g][v] = d + w[t]});
            }
        }
    }
    for (int y=0; y<4; ++y) for (int s=0; s<24; ++s) e[0][y][s] = d[y1][0][y][s][0];
    int b = x2<0 ? L-1 : 1, k = 0, c = 0; x2 = abs(x2);
    for (unsigned int i=x2; (1<<k) <= i; ++k);
    if (k--) {
        memset(a, 1, sizeof(a));
        for (int y=0; y<4; ++y) for (int s=0; s<24; ++s) for (int u=0; u<4; ++u) for (int v=0; v<24; ++v)
            a[y][s][u][v][0] = d[y][s][u][v][b];
        for (int w=1; w<=k; ++w) for (int y=0; y<4; ++y) for (int s=0; s<24; ++s)
        for (int u=0; u<4; ++u) for (int v=0; v<24; ++v) for (int i=0; i<4; ++i) for (int j=0; j<24; ++j)
            a[y][s][u][v][w] = min(a[y][s][u][v][w], a[y][s][i][j][w-1] + a[i][j][u][v][w-1]);
        for (; x2 && k>=0; --k) if ((1<<k) <= x2) {
            for (int y=0; y<4; ++y) for (int s=0; s<24; ++s) {
                long long &r = e[c^1][y][s] = 200000000000;
                for (int u=0; u<4; ++u) for (int v=0; v<24; ++v) r = min(r, e[c][u][v] + a[u][v][y][s][k]);
            }
            c ^= 1; x2 -= 1<<k;
        }
    }
    long long ans = e[c][y2][0];
    for (int i=1; i<24; ++i) ans = min(ans, e[c][y2][i]);
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int k=0; k<t; ++k) {
        if (k) cout << endl;
        solve();
    }
    return 0;
}