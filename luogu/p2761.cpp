/**
 * p2761 软件补丁问题
 * 同UVa658 It’s not a Bug, it’s a Feature!
 */

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define T 22
#define M 110
#define N 1050000
struct edge {int u, v, cap, flow, cost;}; vector<edge> e; map<string, int> id; bool visit[N];
int w[M], a[N], d[N], p[N], m, n, t; char s1[M][T], s2[M][T], s[N][T]; vector<int> g[N];

void addEdge(int u, int v, int cap, int cc) {
    edge ee;
    ee.u = u; ee.v = v; ee.cap = cap; ee.flow = 0; ee.cost = cc; g[u].push_back(e.size()); e.push_back(ee);
    ee.u = v; ee.v = u; ee.cap = 0; ee.flow = 0; ee.cost = -cc; g[v].push_back(e.size()); e.push_back(ee);
}

void build(int u=0) {
    for (short i=0; i<m; ++i) {
        char (&ref)[T] = s[t]; bool ok = true;
        for (short j=0; j<n; ++j) if ((s1[i][j]=='+' && s[u][j]!='+') || (s1[i][j]=='-' && s[u][j]!='-')) {
            ok = false; break;
        }
        if (ok) {
            for (short j=0; j<n; ++j) ref[j] = s2[i][j]=='0' ? s[u][j] : s2[i][j];
            ref[n] = 0; string ss(ref);
            if (!id.count(ss)) g[id[ss] = t].clear(), build(t++);
            short v = id[ss]; if (v > 0) addEdge(u, v, 1, w[i]);
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) {
        id.clear(); s[0][n] = s[1][n] = 0; t = 2; e.clear(); g[0].clear(); g[1].clear();
        for (short i=0; i<n; ++i) s[0][i] = '+'; id[string(s[0])] = 0;
        for (short i=0; i<n; ++i) s[1][i] = '-'; id[string(s[1])] = 1;
        for (short i=0; i<m; ++i) cin >> w[i] >> s1[i] >> s2[i];
        build(); g[t].clear(); addEdge(1, t, 1, 0);
        int cc = 0;
        while (true) {
            memset(d, -1, sizeof(d)); memset(visit, 0, sizeof(visit));
            d[0] = 0; a[0] = 1; vector<int> q; q.push_back(0);
            int head = 0, tail = 1;
            while (head < tail) {
                int u = q[head++]; visit[u] = false;
                for (int i=g[u].size()-1; i>=0; --i) {
                    const edge& ee = e[g[u][i]];
                    if (ee.cap > ee.flow && (d[ee.v] < 0 || d[ee.v] > d[u]+ee.cost)) {
                        d[ee.v] = d[u]+ee.cost;
                        p[ee.v] = g[u][i];
                        a[ee.v] = min(a[u], ee.cap-ee.flow);
                        if (!visit[ee.v]) visit[ee.v] = true, q.push_back(ee.v), ++tail;
                    }
                }
            }
            if (d[t] < 0) break;
            cc += d[t];
            for (int u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        cout << cc << endl;
    }
    return 0;
}