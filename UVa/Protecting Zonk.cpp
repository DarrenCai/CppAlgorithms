/**
 * UVa12093
 * 保卫Zonk
 */

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define N 10100
int n, c1, c2, d[N][3], p[N]; vector<int> edge[N], g[N];

int build(short u = 1) {
    p[u] = 0;
    for (short i=edge[u].size()-1; i>=0; --i) if (g[edge[u][i]].size() == 0) {
        g[u].push_back(edge[u][i]);
        p[u] = max(p[u], 1+build(edge[u][i]));
    }
    return p[u];
}

int dp(short u, short f) {
    int& ref = d[u][f];
    if (ref > -1) return ref;
    if (f == 0) {
        ref = 0; int s = 0;
        if (g[u].size() == 0) return ref;
        for (short i=g[u].size()-1; i>=0; --i) {
            short v = g[u][i]; int c = dp(v, 1), ss = 0;
            s += min(min(dp(v, 0), dp(v, 1)), dp(v, 2));
            for (short j=g[v].size()-1; j>=0; --j) ss += min(min(dp(g[v][j], 0), dp(g[v][j], 1)), dp(g[v][j], 2));
            for (short j=g[v].size()-1; j>=0; --j)
                c = min(c, ss - min(min(d[g[v][j]][0], d[g[v][j]][1]), d[g[v][j]][2]) + d[g[v][j]][2]);
            ref += c;
        }
        for (short i=g[u].size()-1; i>=0; --i)
            ref = min(ref, s - min(min(d[g[u][i]][0], d[g[u][i]][1]), d[g[u][i]][2]) + d[g[u][i]][2]);
    } else if (f == 1) {
        ref = c1;
        for (short i=g[u].size()-1; i>=0; --i)
            ref += min(min(dp(g[u][i], 0), dp(g[u][i], 1)), dp(g[u][i], 2));
    } else {
        ref = c2;
        for (short i=g[u].size()-1, v; i>=0; --i) if (p[v = g[u][i]] > 1) {
            int c = dp(v,2), cc = 0;
            for (short j=g[v].size()-1; j>=0; --j)
                cc += min(min(dp(g[v][j], 0), dp(g[v][j], 1)), dp(g[v][j], 2));
            ref += min(c, cc);
        }
    }
    return ref;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> c1 >> c2 && n) {
        for (short i=1; i<=n; ++i) edge[i].clear(), g[i].clear();
        for (short i=1; i<n; ++i) {
            int u, v; cin >> u >> v;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        build(); memset(d, -1, sizeof(d));
        cout << min(min(dp(1, 0), dp(1, 1)), dp(1, 2)) << endl;
    }
    return 0;
}