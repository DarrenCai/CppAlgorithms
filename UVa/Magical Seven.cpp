/**
 * UVa11276
 * 神奇的七
 */

#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

#define ULL unsigned long long
#define M 10000

namespace PerfectMatch{
    const int T = 70; int a[T][T], b[T][T], c[T][T], d[T], e[T], p[128], t;

    void dfs(int k) {
        if (k & 64) {
            int v = (k^64) << 1;
            if (p[v] < 0) p[v] = t++, dfs(v);
            a[p[k]][p[v]] = b[p[k]][p[v]] = 1;
            if (~k & 1) {
                if (p[v |= 3] < 0) p[v] = t++, dfs(v);
                b[p[k]][p[v]] = 1;
            }
        } else {
            int v = k<<1 | 1;
            if (p[v] < 0) p[v] = t++, dfs(v);
            a[p[k]][p[v]] = b[p[k]][p[v]] = 1;
        }
    }

    void mul(const int (&a)[T][T], const int (&b)[T][T], int (&c)[T][T]) {
        memset(c, 0, sizeof(c));
        for (int i=0; i<t; ++i) for (int k=0; k<t; ++k) if (a[i][k]) for (int j=0; j<t; ++j) if (b[k][j])
            c[i][j] = (c[i][j] + a[i][k]*b[k][j]) % M;
    }

    void pow(ULL n) {
        memcpy(c, a, sizeof(a));
        while (n) {
            if (n & 1) {
                memcpy(e, d, sizeof(d));
                for (int i=0; i<t; ++i) {
                    d[i] = 0;
                    for (int k=0; k<t; ++k) if (e[k]) d[i] = (d[i] + e[k]*c[k][i]) % M;
                }
            }
            if (n == 1) return;
            memcpy(b, c, sizeof(c)); mul(b, b, c); n >>= 1;
        }
    }

    int solve(ULL n) {
        if (n == 1) return a[0][0];
        for (int i=0; i<t; ++i) d[i] = !i;
        pow(n);
        return d[0];
    }

    void init() {
        memset(a, 0, sizeof(a)); memset(b, 0, sizeof(b)); memset(p, -1, sizeof(p));
        p[127] = 0; t = 1; dfs(127);
        for (int i=1; i<7; ++i) memcpy(c, a, sizeof(a)), mul(c, b, a);
    }
}

namespace Halmiton {
    const int T = 319, E = 261; int m[7][T][T], a[T][T], x[4][E][E], d[E], e[E], p[65536], t, s; bool vis[7][T];

    int r_t_l(int k, int i) {
        for (int c=1; i<16; i+=2) {
            int t = k>>i & 3;
            if (t == 1) ++c;
            else if (t == 2 && --c == 0) return k ^ 3<<i;
        }
        return k;
    }

    int l_t_r(int k, int i) {
        for (int c=1; i>=0; i-=2) {
            int t = k>>i & 3;
            if (t == 2) ++c;
            else if (t == 1 && --c == 0) return k ^ 3<<i;
        }
        return k;
    }

    int roll(int v, int i) {
        return i ? v : v<<2;
    }

    #define r(k, i, j, v) \
        if (p[v] < 0) p[v] = t++; \
        if (!vis[j][p[v]]) vis[j][p[v]] = true, dfs(v, j); \
        m[i][p[k]][p[v]] = 1

    void dfs(int k, int i) {
        int l = k>>i>>i & 3, u = k>>i+1>>i+1 & 3, j = i<6 ? i+1 : 0;
        if (!l && !u) {
            if (!j) return;
            int v = k | 9<<i<<i; r(k, i, j, v);
        } else if (!l || !u) {
            int w = k ^ l<<i<<i ^ u<<i+1<<i+1, v = roll(w | l+u<<i<<i, j); r(k, i, j, v);
            if (!j) return;
            v = roll(w | l+u<<i+1<<i+1, j); r(k, i, j, v);
        } else if (l == 2 && u == 1) {
            int v = roll(k ^ 6<<i<<i, j); r(k, i, j, v);
        } else if (l == 1 && u == 1) {
            int v = roll(r_t_l(k ^ 5<<i<<i, (i<<1)+4), j); r(k, i, j, v);
        } else if (l == 2 && u == 2) {
            int v = roll(l_t_r(k ^ 10<<i<<i, (i<<1)-2), j); r(k, i, j, v);
        }
    }

    void mul(const int (&a)[T][T], const int (&b)[T][T], int (&c)[T][T]) {
        memset(c, 0, sizeof(c));
        for (int i=0; i<t; ++i) for (int k=0; k<t; ++k) if (a[i][k]) for (int j=0; j<t; ++j) if (b[k][j])
            c[i][j] = (c[i][j] + a[i][k]*b[k][j]) % M;
    }

    void mul(const int (&a)[E][E], const int (&b)[E][E], int (&c)[E][E]) {
        memset(c, 0, sizeof(c));
        for (int i=0; i<E; ++i) for (int k=0; k<E; ++k) if (a[i][k]) for (int j=0; j<E; ++j) if (b[k][j])
            c[i][j] = (c[i][j] + a[i][k]*b[k][j]) % M;
    }

    void mul(const int (&a)[E], const int (&b)[E][E], int (&c)[E]) {
        memset(c, 0, sizeof(c));
        for (int i=0; i<E; ++i) for (int k=0; k<E; ++k) if (a[k]) c[i] = (c[i] + a[k]*b[k][i]) % M;
    }

    void pow(ULL n) {
        memcpy(x[2], x[1], sizeof(x[1]));
        while (n) {
            if (n & 1) memcpy(e, d, sizeof(d)), mul(e, x[2], d);
            if (n == 1) return;
            memcpy(x[3], x[2], sizeof(x[2])); mul(x[3], x[3], x[2]); n >>= 1;
        }
    }

    int solve(ULL n) {
        for (int i=0; i<E; ++i) d[i] = !i;
        if (n > 1) pow(n-1);
        memcpy(e, d, sizeof(d)); mul(e, x[0], d);
        return d[s];
    }

    void init() {
        memset(m, 0, sizeof(m)); memset(vis, 0, sizeof(vis)); memset(p, -1, sizeof(p));
        p[0] = 0; t = 1; vis[0][0] = true; dfs(0, 0); s = p[36864];
        for (int i=1; i<6; ++i) memcpy(a, m[0], sizeof(a)), mul(a, m[i], m[0]);
        memcpy(a, m[0], sizeof(a)); mul(a, m[6], m[1]);
        memset(p, -1, sizeof(p));
        for (int i=0, k=0; i<t; ++i) for (int j=0; j<t; ++j) if (m[0][i][j] || m[0][j][i] || m[1][i][j] || m[1][j][i]) {
            p[i] = k++; break;
        }
        for (int i=0; i<t; ++i) if (p[i] >= 0) for (int j=0; j<t; ++j) if (p[j] >= 0)
            x[0][p[i]][p[j]] = m[0][i][j], x[1][p[i]][p[j]] = m[1][i][j];
        s = p[s];
    }
}

namespace SpanningSubgraph {
    const int T = 112, E = 82; int a[T][T], b[T][T], c[T][T], d[T][T], x[E][E], y[E][E], z[E][E], e[E], f[E], p[256], t;

    void dfs(int k) {
        int l = k & 1, u = k & 128;
        if (l ^ u>>7) {
            int w = (k^l^u) << 1, v = w | 2;
            if (p[v] < 0) p[v] = t++, dfs(v);
            b[p[k]][p[v]] = c[p[k]][p[v]] = 1;
            if (!l) a[p[k]][p[v]] = 1;
            v = w | 1;
            if (p[v] < 0) p[v] = t++, dfs(v);
            b[p[k]][p[v]] = 1;
            if (!l) a[p[k]][p[v]] = 1;
        } else if (l) {
            int v = (k^l^u) << 1;
            if (p[v] < 0) p[v] = t++, dfs(v);
            a[p[k]][p[v]] = b[p[k]][p[v]] = c[p[k]][p[v]] = 1;
        } else {
            int v = k<<1 | 3;
            if (p[v] < 0) p[v] = t++, dfs(v);
            a[p[k]][p[v]] = b[p[k]][p[v]] = 1;
        }
    }

    void mul(const int (&a)[T][T], const int (&b)[T][T], int (&c)[T][T]) {
        memset(c, 0, sizeof(c));
        for (int i=0; i<t; ++i) for (int k=0; k<t; ++k) if (a[i][k]) for (int j=0; j<t; ++j) if (b[k][j])
            c[i][j] = (c[i][j] + a[i][k]*b[k][j]) % M;
    }

    void mul(const int (&a)[E][E], const int (&b)[E][E], int (&c)[E][E]) {
        memset(c, 0, sizeof(c));
        for (int i=0; i<E; ++i) for (int k=0; k<E; ++k) if (a[i][k]) for (int j=0; j<E; ++j) if (b[k][j])
            c[i][j] = (c[i][j] + a[i][k]*b[k][j]) % M;
    }

    void pow(ULL n) {
        memcpy(y, x, sizeof(x));
        while (n) {
            if (n & 1) {
                memcpy(f, e, sizeof(e));
                for (int i=0; i<E; ++i) {
                    e[i] = 0;
                    for (int k=0; k<E; ++k) if (f[k]) e[i] = (e[i] + f[k]*y[k][i]) % M;
                }
            }
            if (n == 1) return;
            memcpy(z, y, sizeof(y)); mul(z, z, y); n >>= 1;
        }
    }

    int solve(ULL n) {
        if (n == 1) return a[0][0];
        for (int i=0; i<t; ++i) e[i] = !i;
        pow(n);
        return e[0];
    }

    void init() {
        memset(a, 0, sizeof(a)); memset(b, 0, sizeof(b)); memset(p, -1, sizeof(p));
        p[0] = 0; t = 1; dfs(0);
        for (int i=1; i<6; ++i) memcpy(d, a, sizeof(a)), mul(d, b, a);
        memcpy(d, a, sizeof(a)); mul(d, c, a);
        memset(p, -1, sizeof(p));
        for (int i=0, k=0; i<t; ++i) for (int j=0; j<t; ++j) if (a[i][j] || a[j][i]) {
            p[i] = k++; break;
        }
        for (int i=0; i<t; ++i) if (p[i] >= 0) for (int j=0; j<t; ++j) if (p[j] >= 0) x[p[i]][p[j]] = a[i][j];
    }
}

int solve(ULL n) {
    return n&1 ? 0 : (PerfectMatch::solve(n) + Halmiton::solve(n) + SpanningSubgraph::solve(n)) % M;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    PerfectMatch::init(); Halmiton::init(); SpanningSubgraph::init();
    ULL n;
    while (cin >> n) cout << setw(4) << setfill('0') << solve(n) << endl;
    return 0;
}