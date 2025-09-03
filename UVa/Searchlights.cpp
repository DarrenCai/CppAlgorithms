/**
 * UVa1465/LA4841
 * 探照灯
 * Hangzhou 2010
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define M 10010
#define N 102
struct node {int a, x, y;} p[M*N]; int a[N][M], fx[M][N], fy[N][M], sx[M][N], sy[N][M], m, n, s;

bool cmp(const node& u, const node& v) {
    return u.a < v.a;
}

int find(int* f, int x) {
    return x == f[x] ? x : f[x] = find(f, f[x]);
}

void merge(int* f, int* s, int x, int y) {
    int u = find(f, x), v = find(f, y);
    if (u == v) return;
    s[u] += s[v]; f[v] = u;
}

void solve() {
    for (int i=s=0; i<n; ++i) for (int j=0; j<m; ++j)
        cin >> a[i][j], p[s++] = {a[i][j], i, j}, fx[j][i] = i, fy[i][j] = j, sx[j][i] = sy[i][j] = 1;
    sort(p, p+s, cmp);
    int w = 0;
    for (int i=0, cc=0; ; ++cc) {
        if (cc > w) {
            cout << cc << endl;
            return;
        }
        for (; i < s && p[i].a == cc; ++i) {
            int x = p[i].x, y = p[i].y;
            if (x > 0 && a[x-1][y] <= cc) merge(fx[y], sx[y], x, x-1);
            if (x+1 < n && a[x+1][y] < cc) merge(fx[y], sx[y], x, x+1);
            if (y > 0 && a[x][y-1] <= cc) merge(fy[x], sy[x], y, y-1);
            if (y+1 < m && a[x][y+1] < cc) merge(fy[x], sy[x], y, y+1);
            int u = find(fx[y], x), v = find(fy[x], y);
            if (sx[y][u] == n || sy[x][v] == m) {
                cout << "NO ANSWER!" << endl;
                return;
            }
            w = max(w, find(fx[y], 0) == u || find(fx[y], n-1) == u ? sx[y][u] : (sx[y][u]+1) >> 1);
            w = max(w, find(fy[x], 0) == v || find(fy[x], m-1) == v ? sy[x][v] : (sy[x][v]+1) >> 1);
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m && n) solve();
    return 0;
}