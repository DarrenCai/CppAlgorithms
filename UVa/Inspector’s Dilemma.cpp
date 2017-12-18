/**
 * UVa12118
 * 检查员的难题
 */

#include <iostream>
#include <vector>
// #include <cstdio>
using namespace std;

vector<short> g[1001];
bool visit[1001], calc[1001];
short d[1001];

int dfs(short i) {
    int t = 0;
    visit[i] = true;
    if (!calc[i]) {
        if (d[i] & 1) ++t;
        calc[i] = true;
    }
    short size = g[i].size();
    for (short j=0; j<size; ++j) {
        if (!calc[g[i][j]]) {
            if (d[g[i][j]] & 1) ++t;
            calc[g[i][j]] = true;
        }
        if (!visit[g[i][j]]) t += dfs(g[i][j]);
    }
    return t;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short v, t; int e, k=0;
    while (cin >> v >> e >> t && v) {
        for (short i=1; i<=v; ++i) {
            visit[i] = calc[i] = false; d[i] = 0;
        }
        for (int i=0; i<e; ++i) {
            short a, b; cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
            ++ d[a]; ++ d[b];
        }
        int r = 0;
        for (short i=1; i<=v; ++i) {
            if (!visit[i] && g[i].size()) {
                int s = dfs(i);
                r += s ? s : 2;
            }
        }
        if (r) r = (r-2) >> 1;
        cout << "Case " << ++k << ": " << (e+r)*t << endl;
        for (short i=1; i<=v; ++i) g[i].clear();
    }
    return 0;
}