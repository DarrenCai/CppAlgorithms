/**
 * UVa12569
 * 树上的机器人规划（简单版）
 */

#include <iostream>
#include <queue>
#include <map>
#include <cstring>
using namespace std;

int n, m, s, t, T, c; bool g[16][16]; map<int, int> p;

int bfs() {
    p.clear(); p[c] = 0; queue<int> q; q.push(c); int step = 0;
    while (!q.empty()) {
        for (int i=q.size(); i; --i) {
            c = q.front(); q.pop(); s = c>>16;
            if (s == t) return step;
            if (g[s][t] && !(c&1<<t)) {
                int cc = (c&0xffff) | t<<16;
                p[cc] = c; c = cc;
                return step+1;
            }
            for (int u=1; u<=n; ++u)
                if (c&1<<u || u==s)
                    for (int v=1; v<=n; ++v)
                        if (g[u][v] && !(c&1<<v) && v!=s) {
                            int cc = u==s ? (c&0xffff) | v<<16 : (c & ~(1<<u)) | 1<<v;
                            if (!p.count(cc)) p[cc] = c, q.push(cc);
                        }
        }
        ++ step;
    }
    return -1;
}

void printPath(int c) {
    int pre = p[c];
    if (pre) {
        printPath(pre);
        int u=pre>>16, v=c>>16;
        if (u != v) {
            cout << u << ' ' << v << endl;
            return;
        }
        for (int i=1; i<=n; ++i) {
            if (pre&1<<i && !(c&1<<i)) u = i;
            if (c&1<<i && !(pre&1<<i)) v = i;
        }
        cout << u << ' ' << v << endl;
    }
}

int main()
{
    cin >> T;
    for (int k=1; k<=T; ++k) {
        memset(g, 0, sizeof(g));
        cin >> n >> m >> s >> t; c = s<<16;
        for (int i=1; i<=m; ++i) cin >> s, c |= 1<<s;
        for (int i=1; i<n; ++i) { int u, v; cin >> u >> v; g[u][v] = g[v][u] = true; }
        int step = bfs(); cout << "Case " << k << ": " << step << endl;
        if (step != -1) printPath(c); cout << endl;
    }
    return 0;
}