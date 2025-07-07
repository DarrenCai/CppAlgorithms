/**
 * UVa11741
 * 网格覆盖
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define M 10000007
#define N 102
#define T 16

int a[T][T], b[T][T], d[T][T], e[T][T], f[T][T], g[T][T], t[T][T], x[N], y[N], s[N], r, c, m, n, h, kase = 0;

bool cmp(int i, int j) {
    return y[i] < y[j] || (y[i] == y[j] && x[i] < x[j]);
}

void copy(const int (&a)[T][T], int (&b)[T][T]) {
    for (int i=0; i<m; ++i) for (int j=0; j<m; ++j) b[i][j] = a[i][j];
}

void mul(const int (&a)[T][T], const int (&b)[T][T], int (&c)[T][T]) {
    for (int i=0; i<m; ++i) for (int j=0; j<m; ++j) c[i][j] = 0;
    for (int i=0; i<m; ++i) for (int k=0; k<m; ++k) if (a[i][k]) for (int j=0; j<m; ++j) if (b[k][j])
        c[i][j] = (c[i][j] + a[i][k]*(long long)b[k][j]) % M;
}

void pow(int x) {
    copy(f, t);
    while (x) {
        if (x & 1) copy(e, g), mul(g, t, e);
        if (x == 1) return;
        copy(t, g); mul(g, g, t); x >>= 1;
    }
}

int solve() {
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i], s[i] = i;
    sort(s, s+n, cmp);
    m = 1<<r; h = m>>1;
    for (int i=0; i<m; ++i) {
        for (int j=0; j<m; ++j) a[i][j] = b[i][j] = d[i][j] = 0, e[i][j] = i==j;
        if (i&h) {
            a[i][(i^h) << 1] = b[i][(i^h) << 1] = d[i][(i^h) << 1 | 1] = 1;
            if (~i&1) b[i][(i^h) << 1 | 3] = 1;
        } else a[i][i<<1 | 1] = b[i][i<<1 | 1] = 1;
    }
    copy(a, f);
    for (int k=1; k<r; ++k) copy(f, g), mul(g, b, f);
    int rr = 0, cc = 0;
    for (int i=0; i<n; ++i) {
        if (cc > y[s[i]]) continue;
        if (cc < y[s[i]]) {
            if (rr > 0) {
                while (rr++ < r) copy(e, g), mul(g, b, e);
                rr = 0; ++cc;
            }
            if (cc < y[s[i]]) pow(y[s[i]] - cc);
        }
        while (rr <= x[s[i]]) copy(e, g), mul(g, rr==x[s[i]] ? d : (rr ? b : a), e), ++rr;
        rr == r ? (cc = y[s[i]] + 1, rr = 0) : cc = y[s[i]];
    }
    if (rr > 0) {
        while (rr++ < r) copy(e, g), mul(g, b, e);
        rr = 0; ++cc;
    }
    if (cc < c) pow(c - cc);
    return e[m-1][m-1];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> r >> c >> n && r) cout << "Case " << ++kase << ": " << solve() << endl;
    return 0;
}