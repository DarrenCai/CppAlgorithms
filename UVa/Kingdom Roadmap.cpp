/**
 * UVa1670
 * 王国的道路图
 */

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define N 100100
int q[N], n; vector<int> g[N], gg[N];

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
        int head = 0, tail = 0;
        for (int i=1; i<=n; ++i) {
            int s = gg[i].size();
            if (s>1 && head<tail) cout << q[head++] << ' ' << gg[i].back() << endl, --s;
            for (int j=0; j<s; ++j) q[tail++] = gg[i][j];
        }
        for (int i=head+1; i<tail; i+=2) cout << q[i-1] << ' ' << q[i] << endl;
        if ((tail-head)&1) cout << q[0] << ' ' << q[tail-1] << endl;
    }
    return 0;
}