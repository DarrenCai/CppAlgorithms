/**
 * UVa1297/LA2178
 * 最少的车
 * Taipei 2000
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 105
short d[N][N], e[N][N][N], f[N][N][N], x0[N], x1[N], y0[N], y1[N], x, y, xa, xb, ya, yb;

short dy(short y, short x) {
    if (y == yb-1 || x1[y] > x) return y;
    return x1[y+1] > x ? y : dy(y+1, x);
}

short rx(short x, short y) {
    if (x == xb-1 || y1[x] > y) return x;
    return y1[x+1] > y ? x : rx(x+1, y);
}

short solve() {
    short px = x, py = y; xa = x; xb = x; ya = y; yb = y;
    memset(x0, 1, sizeof(x0)); memset(x1, 0, sizeof(x1)); memset(y0, 1, sizeof(y0)); memset(y1, 0, sizeof(y1));
    while (cin>>x>>y && x) {
        if (px == x) for (short i=min(y, py), j=max(y,py); i<j; ++i) x0[i] = min(x0[i], x), x1[i] = max(x1[i], x);
        else for (short i=min(x, px), j=max(x,px); i<j; ++i) y0[i] = min(y0[i], y), y1[i] = max(y1[i], y);
        px = x; py = y; xb = max(x, xb); yb = max(y, yb);
    }
    for (short i=xa; i<px; ++i) y0[i] = ya;
    x1[ya-1] = xa; memset(e, 1, sizeof(e)); memset(f, 1, sizeof(f)); memset(d, 1, sizeof(d)); d[ya-1][xa-1] = 0;
    for (y=ya-1; y<yb; ++y) for (x=xa-1; x<x1[y]; ++x) {
        if (d[y][x] < N) {
            short v = d[y][x]+1, z = x+1;
            if (z < xb-1) {
                for (short k=y+1; k<yb && x0[k]<=z; ++k) {
                    short c = k==y+1 ? z : x1[k-1]-1;
                    if (c <= z) {
                        short &r = d[dy(k, z+1)][rx(z, k+1)]; r = min(r, v);
                    } else e[k][z][c] = min(e[k][z][c], v);
                }
                if ((z = y+1) < yb-1) for (short k=x+2; k<xb && y0[k]<=z; ++k) {
                    short c = y1[k-1]-1;
                    if (c <= z) {
                        short &r = d[dy(z, k+1)][rx(k, z+1)]; r = min(r, v);
                    } else f[z][k][c] = min(f[z][k][c], v);
                }
            } else d[yb-1][z] = min(d[yb-1][z], v);
        }
        if (y > ya) for (short k=x+1; k<x1[y-1]; ++k) if (e[y][x][k] < N) {
            short v = e[y][x][k]+1, c = x+1;
            for (short z=y+1; z<yb && x0[z]<=c; ++z) {
                short t = z==y+1 ? k : x1[z-1]-1;
                if (t <= c) {
                    short &r = d[dy(z, c+1)][rx(c, z+1)]; r = min(r, v);
                } else {
                    short &r = e[z][c][t]; r = min(r, v);
                }
            }
        }
        if (x > xa) for (short k=y+1; k<y1[x-1]; ++k) if (f[y][x][k] < N) {
            short v = f[y][x][k]+1, c = y+1;
            for (short z=x+1; z<xb && y0[z]<=c; ++z) {
                short t = z==x+1 ? k : y1[z-1]-1;
                if (t <= c) {
                    short &r = d[dy(c, z+1)][rx(z, c+1)]; r = min(r, v);
                } else {
                    short &r = f[c][z][t]; r = min(r, v);
                }
            }
        }
    }
    return d[yb-1][xb-1];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short k = 0;
    while (cin>>x>>y && x) cout << ++k << ' ' << solve() << endl;
    return 0;
}