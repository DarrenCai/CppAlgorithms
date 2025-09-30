/**
 * UVa1063/LA3807
 * 滚球游戏
 * World Finals 2007
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 50001
#define N 4
int a[N][N], e[N][N], f[N][N], h[N][N], q[M], m, n, w, c, kase = 0;
long long s[M], g[M]; bool l[N][N], r[N][N], t[N][N], b[N][N];

bool term() {
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) if (f[i][j]) return false;
    return true;
}

void decode(long long x, long long y) {
    for (int i=n-1; i>=0; --i) for (int j=n-1; j>=0; --j) a[i][j] = x & 15, h[i][j] = y & 15, x >>= 4, y >>= 4;
}

void insert() {
    long long x = 0, y = 0;
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) x = x<<4 | e[i][j], y = y<<4 | f[i][j];
    int k = x % M;
    while (s[k]) {
        if (s[k] == x) return;
        ++ k;
    }
    s[k] = x; g[k] = y; q[c++] = k;
}

bool move_l() {
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) e[i][j] = a[i][j], f[i][j] = h[i][j];
    for (int i=0; i<n; ++i) for (int j=n-2, k; j>=0; --j) if (f[i][j]) {
        for (k=j+1; !l[i][k] && !f[i][k]; ++k) if (e[i][k]) {
            if (e[i][k] != f[i][j]) return false;
            e[i][k] = f[i][j] = 0; break;
        }
    }
    for (int i=0; i<n; ++i) for (int j=0, k; j<n; ++j) if (!e[i][j]) {
        for (k=j; !r[i][k]; ++k) if (e[i][k]) break;
        if (k > j) e[i][j] = e[i][k], e[i][k] = 0;
    }
    return true;
}

bool move_r() {
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) e[i][j] = a[i][j], f[i][j] = h[i][j];
    for (int i=0; i<n; ++i) for (int j=1, k; j<n; ++j) if (f[i][j]) {
        for (k=j-1; !r[i][k] && !f[i][k]; --k) if (e[i][k]) {
            if (e[i][k] != f[i][j]) return false;
            e[i][k] = f[i][j] = 0; break;
        }
    }
    for (int i=0; i<n; ++i) for (int j=n-1, k; j>0; --j) if (!e[i][j]) {
        for (k=j; !l[i][k]; --k) if (e[i][k]) break;
        if (k < j) e[i][j] = e[i][k], e[i][k] = 0;
    }
    return true;
}

bool move_t() {
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) e[i][j] = a[i][j], f[i][j] = h[i][j];
    for (int j=0; j<n; ++j) for (int i=n-2, k; i>=0; --i) if (f[i][j]) {
        for (k=i+1; !t[k][j] && !f[k][j]; ++k) if (e[k][j]) {
            if (e[k][j] != f[i][j]) return false;
            e[k][j] = f[i][j] = 0; break;
        }
    }
    for (int j=0; j<n; ++j) for (int i=0, k; i<n; ++i) if (!e[i][j]) {
        for (k=i; !b[k][j]; ++k) if (e[k][j]) break;
        if (k > i) e[i][j] = e[k][j], e[k][j] = 0;
    }
    return true;
}

bool move_b() {
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) e[i][j] = a[i][j], f[i][j] = h[i][j];
    for (int j=0; j<n; ++j) for (int i=1, k; i<n; ++i) if (f[i][j]) {
        for (k=i-1; !b[k][j] && !f[k][j]; --k) if (e[k][j]) {
            if (e[k][j] != f[i][j]) return false;
            e[k][j] = f[i][j] = 0; break;
        }
    }
    for (int j=0; j<n; ++j) for (int i=n-1, k; i>=0; --i) if (!e[i][j]) {
        for (k=i; !t[k][j]; --k) if (e[k][j]) break;
        if (k < i) e[i][j] = e[k][j], e[k][j] = 0;
    }
    return true;
}

int solve() {
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j)
        e[i][j] = f[i][j] = 0, l[i][j] = j==0, r[i][j] = j==n-1, t[i][j] = i==0, b[i][j] = i==n-1;
    for (int i=1, j, k; i<=m; ++i) cin >> j >> k, e[j][k] = i;
    for (int i=1, j, k; i<=m; ++i) cin >> j >> k, e[j][k] == i ? e[j][k] = 0 : f[j][k] = i;
    for (int i=0; i<w; ++i) {
        int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
        if (r1 == r2) r[r1][min(c1, c2)] = l[r1][max(c1, c2)] = true;
        else t[max(r1, r2)][c1] = b[min(r1, r2)][c1] = true;
    }
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) if (e[i][j] && f[i][j] && e[i][j] != f[i][j]) return -1;
    if (term()) return 0;
    memset(s, c = 0, sizeof(s)); insert();
    int h = 0, t = c, d = 1;
    while (h < t) {
        long long x = s[q[h]], y = g[q[h++]]; decode(x, y);
        if (move_l()) {
            if (term()) return d;
            insert();
        }
        if (move_r()) {
            if (term()) return d;
            insert();
        }
        if (move_t()) {
            if (term()) return d;
            insert();
        }
        if (move_b()) {
            if (term()) return d;
            insert();
        }
        if (h == t) t = c, ++d;
    }
    return -1;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m >> w && n) {
        int k = solve();
        cout << "Case " << ++kase << ": ";
        k < 0 ? cout << "impossible" << endl << endl : cout << k << " moves" << endl << endl;
    }
    return 0;
}