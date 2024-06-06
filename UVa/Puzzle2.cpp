/**
 * UVa1116/LA2429
 * CERC 2001
 */

#include <iostream>
#include <queue>
#include <set>
using namespace std;

#define N 10020
struct node {
    int u, d;
    bool operator< (const node& rhs) const{
        return d > rhs.d;
    }
};
int s[N][3], g[N][2], c[N], m, n; set<int> e[N];

void solve() {
    cin >> n >> m;
    for (int i=1; i<=n; ++i) c[i] = 0, e[i].clear();
    for (int i=m+n; i>0; --i) {
        int u, v; cin >> u >> v; e[u].insert(v); e[v].insert(u);
    }
    priority_queue<node> q; int h = 1, t = 0;
    for (int i=1; i<=n; ++i) q.push({i, int(e[i].size())});
    while (!q.empty()) {
        node r = q.top(); q.pop(); int u = r.u;
        if (c[u] == 2) continue;
        if (e[u].size() == 1) {
            int v = *e[u].begin(); g[u][c[u]++] = v; g[v][c[v]++] = u;
            break;
        }
        set<int>::iterator it = e[u].begin(); int a = *it, b = *++it;
        g[u][c[u]++] = a; g[u][c[u]++] = b; e[a].erase(u); e[b].erase(u);
        if (!e[a].count(b)) e[a].insert(b), e[b].insert(a);
        else q.push({a, int(e[a].size())}), q.push({b, int(e[b].size())});
        s[t][0] = u; s[t][1] = a; s[t++][2] = b;
    }
    while (t--) {
        int u = s[t][0], a = s[t][1], b = s[t][2];
        g[a][0] == b ? g[a][0] = u : g[a][1] = u; g[b][0] == a ? g[b][0] = u : g[b][1] = u;
    }
    cout << 1; t = min(g[1][0], g[1][1]);
    while (t != 1) {
        cout << ' ' << t;
        for (int i=0, v; i<2; ++i) if ((v = g[t][i]) != h) {
            h = t; t = v; break;
        }
    }
    cout << endl;
    return;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        solve();
        if (t) cout << endl;
    }
    return 0;
}