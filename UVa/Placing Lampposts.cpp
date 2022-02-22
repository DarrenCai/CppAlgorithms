/**
 * UVa10859
 * 放置街灯
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1020
struct {short c, d;} d[N][2], ans; short g[N][N], c[N], p[N], n, m;

short find(short x) {
    return x==p[x] ? x : p[x] = find(p[x]);
}

void dfs(short u, short fa = -1) {
    short &c0 = d[u][0].c = 0, &d0 = d[u][0].d = 0, &c1 = d[u][1].c = c[u], &d1 = d[u][1].d = 1;
    for (short i=0, v; i<c[u]; ++i) if ((v = g[u][i]) != fa) {
        dfs(v, u);
        const short &cc0 = d[v][0].c, &dd0 = d[v][0].d, &cc1 = d[v][1].c, &dd1 = d[v][1].d;
        c0 += cc1; d0 += dd1;
        dd0 < dd1 || (dd0 == dd1 && cc0 > cc1) ? (c1 += cc0, d1 += dd0) : (c1 += cc1, d1 += dd1);
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t, a, b; cin >> t;
    while (t--) {
        cin >> n >> m;
        memset(c, ans.c = ans.d = 0, sizeof(c));
        for (short i=0; i<n; ++i) p[i] = i;
        for (short i=0; i<m; ++i) cin >> a >> b, g[a][c[a]++] = b, g[b][c[b]++] = a, p[find(b)] = find(a);
        for (short i=0; i<n; ++i) if (p[i] == i) {
            dfs(i);
            const short &c0 = d[i][0].c, &d0 = d[i][0].d, &c1 = d[i][1].c, &d1 = d[i][1].d;
            d0 < d1 || (d0 == d1 && c0 > c1) ? (ans.c += c0, ans.d += d0) : (ans.c += c1, ans.d += d1);
        }
        cout << ans.d << ' ' << ans.c-m << ' ' << 2*m-ans.c << endl;
    }
    return 0;
}