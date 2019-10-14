/**
 * UVa1613
 * K度图的着色
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <set>
using namespace std;

#define N 10000
vector<short> g[N]; set<short> s; short n, k, c[N], q[N], h, t; int m;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    bool flag = true;
    while (cin >> n >> m) {
        memset(c+1, 0, n*sizeof(short)); c[1] = q[h=0] = t = k = 1;
        for (short i=1; i<=n; ++i) g[i].clear();
        for (int i=0; i<m; ++i) {
            short u, v; cin >> u >> v;
            g[u].push_back(v); g[v].push_back(u);
            if (g[u].size() > k) k = g[u].size();
            if (g[v].size() > k) k = g[v].size();
        }
        if (!(k&1)) ++k;
        while (h < t) {
            short u = q[h++];
            for (short i=g[u].size()-1; i>=0; --i)
                if (!c[g[u][i]]) {
                    for (short j=1; j<=k; ++j) s.insert(j);
                    for (short j=g[g[u][i]].size()-1; j>=0; --j) s.erase(c[g[g[u][i]][j]]);
                    c[g[u][i]] = *s.begin();
                    q[t++] = g[u][i];
                }
        }
        if (!flag) cout << endl;
        else flag = false;
        cout << k << endl;
        for (short i=1; i<=n; ++i) cout << c[i] << endl;
    }
    return 0;
}