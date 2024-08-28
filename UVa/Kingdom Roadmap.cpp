/**
 * UVa1670/LA5920
 * 王国的道路图
 * NEERC 2011
 */

#include <iostream>
#include <vector>
using namespace std;

#define N 100100
int q[N], n; vector<int> g[N], gg[N];

void solve() {
    int c = 0;
    for (int i=1; i<=n; ++i) g[i].clear(), gg[i].clear();
    for (int i=1, u, v; i<n; ++i) cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
    for (int i=1; i<=n; ++i) if (g[i].size() == 1) {
        int u = g[i][0], p = i, v; ++c;
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
    if (c&1) cout << q[0] << ' ' << q[tail-1] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n) solve();
    return 0;
}