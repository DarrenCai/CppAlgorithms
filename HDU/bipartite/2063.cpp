/**
 * HDU2063
 * https://acm.hdu.edu.cn/showproblem.php?pid=2063
 * 过山车
 * 二分图最大匹配
 */

#include <iostream>
using namespace std;

#define N 502
int g[N][N], c[N], p[N<<1], vis[N<<1], m, nx, ny, clk;

bool dfs(int u) {
    vis[u] = clk;
    for (int i=0, v; i<c[u]; ++i) if (p[v = g[u][i]] < 0 || (vis[p[v]]!=clk && dfs(p[v]))) {
        p[u] = v; p[v] = u;
        return true;
    }
    return false;
}

int augment_path() {
    cin >> nx >> ny;
    for (int i=1; i<=nx; ++i) c[i] = 0, p[i] = vis[i] = -1;
    for (int i=1; i<=ny; ++i) p[i+nx] = vis[i+nx] = -1;
    while (m--) {
        int u, v; cin >> u >> v; g[u][c[u]++] = v+nx;
    }
    int cc = 0;
    for (int i=clk=1; i<=nx; ++i, ++clk) if (p[i] < 0 && dfs(i)) ++cc;
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> m && m) cout << augment_path() << endl;
    return 0;
}