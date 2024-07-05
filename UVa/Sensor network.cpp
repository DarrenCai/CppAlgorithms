/**
 * UVa12275/LA4960
 * SWERC 2010
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 352
struct edge {
    int u, v, w;
    bool operator< (const edge &rhs) const {
        return w < rhs.w;
    }
} e[N*N>>1];
int f[N], s[N], m, n, l, r, ans;

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

void upd() {
    l = s[1]; r = s[n-1]; ans = min(ans, e[r].w - e[l].w);
    for (int i=0; i<n; ++i) f[i] = i;
    for (int i=2; i<n; ++i) f[find(e[s[i]].u)] = find(e[s[i]].v);
}

void kruskal() {
    sort(e, e+m);
    for (int i=0; i<n; ++i) f[i] = i;
    int cc = 1;
    for (int i=0; i<m; ++i) {
        int u = find(e[i].u), v = find(e[i].v);
        if (u == v) continue;
        f[u] = v; s[cc] = i;
        if (++cc == n) return upd();
    }
}

void insert(int x) {
    int k = lower_bound(s+2, s+n, x) - s - 1;
    for (int i=1; i<k; ++i) s[i] = s[i+1];
    s[k] = x;
}

int solve () {
    cin >> m; ans = 1<<16;
    for (int i=0; i<m; ++i) cin >> e[i].u >> e[i].v >> e[i].w;
    kruskal();
    for (int i=l+1; i<=m; ++i) {
        if (i == m) break;
        if (find(e[i].u) != find(e[i].v)) insert(i), upd(), i = l;
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n && n) cout << solve() << endl;
}