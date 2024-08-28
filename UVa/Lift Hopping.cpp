/**
 * UVa10801
 * 电梯换乘
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define INF 0x7f7f7f7f
#define M 5
#define N 100
struct node {
    int u, d;
    bool operator< (const node& rhs) const {
        return d > rhs.d;
    }
};
int t[M], d[N], m, n, k; bool v[M][N], f[N];

void solve() {
    memset(d, 127, sizeof(d)); memset(f, m = 0, sizeof(f)); memset(v, 0, sizeof(v));
    for (int i=0; i<n; ++i) cin >> t[i];
    for (int i=0; i<n; ++i) {
        int x; cin >> x; v[i][x] = true; m = max(m, x);
        while (cin.peek() != '\n') cin >> x, v[i][x] = true, m = max(m, x);
    }
    priority_queue<node> q;
    for (int i=0; i<n; ++i) if (v[i][0]) for (int j=0; j<=m; ++j) if (v[i][j] && j*t[i] < d[j])
        q.push({j, d[j] = j*t[i]});
    while (!q.empty()) {
        int u = q.top().u, d1; q.pop();
        if (u == k) break;
        if (f[u]) continue;
        f[u] = true;
        for (int i=0; i<n; ++i) if (v[i][u]) for (int k=0; k<=m; ++k)
            if (v[i][k] && (d1 = d[u]+60+abs(u-k)*t[i]) < d[k]) q.push({k, d[k] = d1});
    }
    d[k] >= INF ? cout << "IMPOSSIBLE" << endl : cout << d[k] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> k) solve();
    return 0;
}