/**
 * UVa1078/LA4128
 * 蒸汽式压路机
 * World Finals >> 2008 - Banff
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define INF 10000000
#define N 102
int d[N][N][4][2], f[N][N][4][2], w1[N][N], w2[N][N], r, c, r1, c1, r2, c2, kase = 0;
struct node {int r, c, k, w;} t;

int bfs() {
    if (r1==r2 && c1==c2) return 0;
    queue<node> q; int e = INF;
    memset(d, 1, sizeof(d)); memset(f, 0, sizeof(f));
    if (r1 > 1 && w2[c1][r1-1]) {
        int d0 = 2*w2[c1][r1-1];
        q.push({r1-1, c1, 0, 0}); d[r1-1][c1][0][1] = d0; f[r1-1][c1][0][1] = 1;
        if (r1-1 == r2 && c1 == c2) e = min(e, d0);
    }
    if (r1 < r && w2[c1][r1]) {
        int d3 = 2*w2[c1][r1];
        q.push({r1+1, c1, 3, 0}); d[r1+1][c1][3][1] = d3; f[r1+1][c1][3][1] = 1;
        if (r1+1 == r2 && c1 == c2) e = min(e, d3);
    }
    if (c1 > 1 && w1[r1][c1-1]) {
        int d1 = 2*w1[r1][c1-1];
        q.push({r1, c1-1, 1, 0}); d[r1][c1-1][1][1] = d1; f[r1][c1-1][1][1] = 1;
        if (r1 == r2 && c1-1 == c2) e = min(e, d1);
    }
    if (c1 < c && w1[r1][c1]) {
        int d2 = 2*w1[r1][c1];
        q.push({r1, c1+1, 2, 0}); d[r1][c1+1][2][1] = d2; f[r1][c1+1][2][1] = 1;
        if (r1 == r2 && c1+1 == c2) e = min(e, d2);
    }
    while (!q.empty()) {
        t = q.front(); q.pop();
        int i = t.r, j = t.c, k = t.k, w = t.w, g = d[i][j][k][w==0]; f[i][j][k][w==0] = 0;
        if (i > 1 && w2[j][i-1]) {
            int d0 = g + (k==0 ? w2[j][i-1] : w + 2*w2[j][i-1]);
            if (d0 < d[i-1][j][0][k!=0]) {
                d[i-1][j][0][k!=0] = d0;
                if (!f[i-1][j][0][k!=0]) q.push({i-1, j, 0, k==0 ? w2[j][i-1] : 0}), f[i-1][j][0][k!=0] = 1;
            }
            if (i-1 == r2 && j == c2) e = min(e, g + 2*w2[j][i-1] + (k==0 ? 0 : w));
        }
        if (i < r && w2[j][i]) {
            int d3 = g + (k==3 ? w2[j][i] : w + 2*w2[j][i]);
            if (d3 < d[i+1][j][3][k!=3]) {
                d[i+1][j][3][k!=3] = d3;
                if (!f[i+1][j][3][k!=3]) q.push({i+1, j, 3, k==3 ? w2[j][i] : 0}), f[i+1][j][3][k!=3] = 1;
            }
            if (i+1 == r2 && j == c2) e = min(e, g + 2*w2[j][i] + (k==3 ? 0 : w));
        }
        if (j > 1 && w1[i][j-1]) {
            int d1 = g + (k==1 ? w1[i][j-1] : w + 2*w1[i][j-1]);
            if (d1 < d[i][j-1][1][k!=1]) {
                d[i][j-1][1][k!=1] = d1;
                if (!f[i][j-1][1][k!=1]) q.push({i, j-1, 1, k==1 ? w1[i][j-1] : 0}), f[i][j-1][1][k!=1] = 1;
            }
            if (i == r2 && j-1 == c2) e = min(e, g + 2*w1[i][j-1] + (k==1 ? 0 : w));
        }
        if (j < c && w1[i][j]) {
            int d2 = g + (k==2 ? w1[i][j] : w + 2*w1[i][j]);
            if (d2 < d[i][j+1][2][k!=2]) {
                d[i][j+1][2][k!=2] = d2;
                if (!f[i][j+1][2][k!=2]) q.push({i, j+1, 2, k==2 ? w1[i][j] : 0}), f[i][j+1][2][k!=2] = 1;
            }
            if (i == r2 && j+1 == c2) e = min(e, g + 2*w1[i][j] + (k==2 ? 0 : w));
        }
    }
    return e;
}

void solve() {
    for (int i=1; i<=r; ++i) {
        for (int j=1; j<c; ++j) cin >> w1[i][j];
        if (i < r) for (int j=1; j<=c; ++j) cin >> w2[j][i];
    }
    int ans = bfs();
    cout << "Case " << ++kase << ": ";
    ans >= INF ? cout << "Impossible" << endl : cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin>>r>>c>>r1>>c1>>r2>>c2 && r) solve();
    return 0;
}