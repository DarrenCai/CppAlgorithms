/**
 * UVa1361/LA3514
 * 无向仙人掌
 * NEERC 2005
 */

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

#define M 1000000
#define N 20100
int s[M][2], g[N][N], c[N], t[N], e[N], pre[N], bn[N], f[N], clk, cc, p, m, n, k, kase = 0;

struct intg {
    int v[670], n;
    void operator= (int x) {
        v[0] = x; n = 1;
    }
    void mul(const intg& a, long long x) {
        long long r = 0;
        for (int i=n=0; i<a.n; ++i) r += a.v[i] * x, v[n++] = r%1000000000, r /= 1000000000;
        if (r) v[n++] = r;
    }
    void print() {
        cout << v[n-1];
        for (int i=n-2; i>=0; --i) cout << setw(9) << setfill('0') << v[i];
        cout << endl;
    }
} d[2];

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

int dfs(int u, int fa = -1) {
    int low = pre[u] = ++clk;
    for (int i=0, v; i<c[u]; ++i) if (!pre[v = g[u][i]]) {
        s[p][0] = u; s[p++][1] = v;
        int lowv = dfs(v, u); low = min(low, lowv);
        if (lowv >= pre[u]) {
            t[++cc] = 0; e[cc] = 0;
            while (true) {
                int x = s[--p][0], y = s[p][1]; ++e[cc];
                if (bn[x] != cc) ++t[cc], bn[x] = cc;
                if (bn[y] != cc) ++t[cc], bn[y] = cc;
                if (x == u && y == v) break;
            }
        }
    } else if (pre[v] < pre[u] && v != fa) {
        s[p][0] = u; s[p++][1] = v; low = min(low, pre[v]);
    }
    return low;
}

void solve() {
    memset(pre, clk = k = 0, sizeof(pre)); memset(bn, cc = p = 0, sizeof(bn));
    for (int i=1; i<=n; ++i) c[f[i] = i] = 0;
    while (m--) {
        int t, x, y; cin >> t >> x;
        while (--t) cin >> y, g[x][c[x]++] = y, g[y][c[y]++] = x, f[find(y)] = find(x), x = y;
    }
    if (kase++) cout << endl;
    for (int i=1, c=0; i<=n; ++i) if (find(i) == i) if (++c > 1) {
        cout << 0 << endl; return;
    }
    for (int u=1; u<=n; ++u) if (!pre[u]) dfs(u);
    d[0] = 1;
    for (int i=1; i<=cc; ++i) {
        if (e[i]>1 && t[i]!=e[i]) {
            cout << 0 << endl; return;
        }
        d[i&1].mul(d[~i&1], e[i]>1 ? e[i]+1 : 1);
    }
    d[cc&1].print();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) solve();
    return 0;
}