/**
 * UVa1670
 * 王国的道路图
 */

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define N 100100
int a[N], q[N], n; vector<int> g[N], gg[N];

bool cmp(int x, int y) {
    return gg[x].size() > gg[y].size();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) {
        int c = 0, u, v;
        for (int i=1; i<=n; ++i) g[i].clear(), gg[i].clear();
        for (int i=1; i<n; ++i) cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
        for (int i=1; i<=n; ++i) if (g[i].size() == 1) {
            ++c; u = g[i][0]; int p = i;
            while (g[u].size() == 2) v = u, u = g[u][0]+g[u][1]-p, p = v;
            gg[u].push_back(i);
        }
        cout << (c+1)/2 << endl;
        u = 0; for (int i=1; i<=n; ++i) if (gg[i].size() > 0) a[u++] = i;
        sort(a, a+u, cmp);
        int head = 0, tail = gg[a[0]].size();
        for (int i=0; i<tail; ++i) q[i] = gg[a[0]][i];
        for (int i=1; i<u; ++i) {
            vector<int>& g = gg[a[i]];
            if (g.size() > 1) {
                cout << q[head++] << ' ' << g.back() << endl;
                for (int j=g.size()-2; j>=0; --j) q[tail++] = g[j];
            } else q[tail++] = g[0];
        }
        for (int i=head+1; i<tail; i+=2) cout << q[i-1] << ' ' << q[i] << endl;
        if ((tail-head)&1) cout << q[0] << ' ' << q[tail-1] << endl;
    }
    return 0;
}