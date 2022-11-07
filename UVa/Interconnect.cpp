/**
 * UVa1390
 * 互联
 * 某一层的状态数可用动态规划推导出来：
    int d[N][N] = {0};
    for (int i=1; i<N; ++i) {
        d[i][i] = d[i][1] = 1;
        for (int j=2; j<i; ++j) {
            for (int k=min(i-j, j); k>0; --k) {
                d[i][j] += d[i-j][k];
            }
        }
    }
    n <= 32 时，状态数最大的层有900多个状态
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 33
#define M 1000

short n, m, t[N], fa[N], g[N][M][N]; bool e[N][N]; double d[N][M];
bool same(const short (&c1)[N], const short (&c2)[N]) {
    for (short i=1; i<=n; ++i) if (c1[i] != c2[i]) return false;
    return true;
}

double calc(short i, short j) {
    double &ref = d[i][j];
    if (ref >= 0.) return ref;
    short (&gg)[N] = g[i][j];
    if (gg[n] == 1) return ref = 0.;
    short m0 = 0; double e = 0.;
    for (short k=1; k<=n; ++k) if (gg[k]>0) {
        m0 += k*(k-1)/2*gg[k];
        for (short l=k; l<=n; ++l) if ((l==k && gg[l]>1) || (l>k && gg[l]>0)) {
            ++gg[k+l]; --gg[k]; --gg[l]; short idx = -1;
            for (short jj=0; jj<t[i+1]; ++jj) if (same(gg, g[i+1][jj])) {
                idx = jj;
                break;
            }
            if (idx == -1) memcpy(g[i+1][idx = t[i+1]++], gg, sizeof(gg));
            --gg[k+l]; ++gg[k]; ++gg[l];
            e += (k==l ? gg[k]*(gg[k]-1)/2*k : gg[k]*gg[l]*l) * k * calc(i+1, idx);
        }
    }
    return ref = (e+m) / (m-m0);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(6);
    while (cin >> n >> m) {
        memset(e, 0, sizeof(e));
        for (short i=1; i<=n; ++i) fa[i] = i;
        while (m--) {
            short u, v; cin >> u >> v;
            if (u == v) continue;
            if (u > v) u += v, v = u-v, u = u-v;
            e[u][v] = true;
        }
        for (short u=1; u<=n; ++u) for (short v=1; v<=n; ++v) if (e[u][v] || e[v][u]) {
            short f = min(fa[u], fa[v]);
            if (f < fa[u]) for (short vv = fa[u]; vv<u; ++vv) if (fa[vv] == fa[u]) fa[vv] = f;
            if (f < fa[v]) for (short vv = fa[v]; vv<v; ++vv) if (fa[vv] == fa[v]) fa[vv] = f;
            fa[u] = fa[v] = f;
        }
        memset(g[0][0], 0, sizeof(g[0][0]));
        for (short u=1; u<=n; ++u) if (fa[u] == u) {
            short s = 1; for (short v=u+1; v<=n; ++v) if (fa[v] == fa[u]) ++s;
            ++g[0][0][s];
        }
        if (g[0][0][n] == 1) {
            cout << 0. << endl;
        } else {
            m = n*(n-1)/2;
            memset(t, 0, sizeof(t));
            for (short i=0; i<n; ++i) fill_n(d[i], M, -1.);
            cout << calc(0, 0) << endl;
        }
    }
    return 0;
}
