/**
 * UVa10615
 * 车
 * 二分图边着色，利用Vizing定理（维金定理）构造解，O(VE)
 * https://oiwiki.org/graph/color/#vizing-%E5%AE%9A%E7%90%86
 * 其实数据规模如果再小一点，可以建图跑最大流
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 102
struct {int u, v, c;} e[N*N]; int c[N<<1][N], d[N<<1], s[N][N], m, n, cc;

void augment(int u, int c1, int c2) {
    if (!c[u][c1]) {
        c[u][c2] = 0;
        return;
    }
    int i = c[u][c1], v = e[i].u + e[i].v - u;
    augment(v, c2, c1); e[i].c = c2; c[u][c2] = c[v][c2] = i;
}

void solve () {
    cin >> n;
    memset(c, 0, sizeof(c)); memset(d, 0, sizeof(d)); memset(s, 0, sizeof(s));
    for (int i=m=0; i<n; ++i) for (int j=0; j<n; ++j) {
        char ch; cin >> ch;
        if (ch == '*') {
            int v = j+n, cx = N, cy = N;
            for (int k=1; k<=n; ++k) {
                if (!c[i][k]) cx = min(cx, k);
                if (!c[v][k]) cy = min(cy, k);
            }
            if (cx < cy) augment(v, cx, cy);
            else if (cy < cx) augment(i, cy, cx);
            cx = min(cx, cy); c[i][cx] = c[v][cx] = ++m; e[m] = {i, v, cx}; ++d[i]; ++d[v];
        }
    }
    for (int i=cc=0; i<n; ++i) cc = max(cc, max(d[i], d[i+n]));
    for (int i=1; i<=m; ++i) s[e[i].u][e[i].v-n] = e[i].c;
    cout << cc << endl;
    for (int i=0; i<n; ++i) {
        cout << s[i][0];
        for (int j=1; j<n; ++j) cout << ' ' << s[i][j];
        cout << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}