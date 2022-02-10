/**
 * UVa1267
 * ⽹络
 */

#include <iostream>
#include <set>
using namespace std;

#define N 1020
short g[N][N], cnt[N], p[N], d[N], n, s, k;
struct cmp {
    bool operator() (short a, short b) const {
        return d[a] > d[b] || (d[a]==d[b] && a<b);
    }
};
set<short, cmp> ss;

void dfs(short u, short fa) {
    for (short i=0; i<cnt[u]; ++i) {
        short v = g[u][i];
        if (v != fa) {
            d[v] = d[u] + 1; p[v] = u;
            if (cnt[v] > 1) dfs(v, u);
            else if (d[v] > k) ss.insert(v);
        }
    }
}

void dfs(short u, short d, short fa) {
    if (++d > k) return;
    for (short i=0; i<cnt[u]; ++i) {
        short v = g[u][i];
        if (v != fa) {
            if (cnt[v] > 1) dfs(v, d, u);
            else ss.erase(v);
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        cin >> n >> s >> k; d[s] = 0; ss.clear();
        for (short i=1; i<=n; ++i) cnt[i] = 0;
        for (short i=1; i<n; ++i) {
            short u, v; cin >> u >> v;
            g[u][cnt[u]++] = v; g[v][cnt[v]++] = u;
        }
        dfs(s, -1); short ans = 0;
        while (!ss.empty()) {
            short u = *ss.begin(), f = u; ss.erase(u); ++ans;
            for (short i=0; i<k; ++i) f = p[f];
            dfs(f, 0, -1);
        }
        cout << ans << endl;
    }
    return 0;
}