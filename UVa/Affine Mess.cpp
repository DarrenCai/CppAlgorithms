/**
 * UVa1102/LA5129
 * 仿射变换
 * World Finals >> 2011 - Orlando
 * 注意：旋转180度等价于缩放(-1,-1)
 */

#include <iostream>
#include <cmath>
using namespace std;

int x1, y, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, kase = 0;

void rot_snap(int x, int y, int rx, int ry, int &u, int &v) {
    double s = sqrt(rx*rx + ry*ry);
    u = round((x*rx - y*ry) / s); v= round((y*rx + x*ry) / s);
}

int trans(int x, int y, int z, int a, int b, int c) {
    if (x == y) {
        if (a != b) return 0;
        if (y == z) return b == c ? 2 : 0;
        return b != c && (b-c) % (y-z) == 0;
    }
    if (a == b || (a-b) % (x-y)) return 0;
    return (a-b) / (x-y) * (z - x) + a == c;
}

int solve(int rx, int ry) {
    int u1, v1, u2, v2, u3, v3;
    rot_snap(x1, y, rx, ry, u1, v1); rot_snap(x2, y2, rx, ry, u2, v2); rot_snap(x3, y3, rx, ry, u3, v3);
    return trans(u1, u2, u3, x4, x5, x6) * trans(v1, v2, v3, y4, y5, y6)
         + trans(u1, u2, u3, x4, x6, x5) * trans(v1, v2, v3, y4, y6, y5)
         + trans(u1, u2, u3, x5, x4, x6) * trans(v1, v2, v3, y5, y4, y6)
         + trans(u1, u2, u3, x5, x6, x4) * trans(v1, v2, v3, y5, y6, y4)
         + trans(u1, u2, u3, x6, x4, x5) * trans(v1, v2, v3, y6, y4, y5)
         + trans(u1, u2, u3, x6, x5, x4) * trans(v1, v2, v3, y6, y5, y4);
}

void print(int s) {
    cout << "Case " << ++kase << ": " << (s > 1 ? "inconsistent solutions" : (s ? "equivalent solutions" : "no solution")) << endl;
}

void solve() {
    int c = 0; cin >> x4 >> y4 >> x5 >> y5 >> x6 >> y6;
    for (int x=-9; x<11; ++x) {
        c += solve(x, 10);
        if (c > 1) return print(c);
        c += solve(-10, x);
        if (c > 1) return print(c);
    }
    return print(c);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> x1 >> y >> x2 >> y2 >> x3 >> y3 && (x1 || y || x2 || y2 || x3 || y3)) solve();
    return 0;
}