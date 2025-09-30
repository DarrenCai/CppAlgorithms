/**
 * UVa1353/LA3402
 * Tokyo 2005
 */

#include <iostream>
#include <cstring>
#include <set>
using namespace std;

struct {bool w1, w2; int v;} g[4][12]; int c[4], x, y;
struct node {
    char s[4][14];
    bool operator< (const node &rhs) const {
        for (int i=0; i<x; ++i) {
            int k = strcmp(s[i], rhs.s[i]);
            if (k) return k < 0;
        }
        return false;
    }
} q[2000000], s, t;

bool check(const node &s) {
    for (int i=0; i<x; ++i) if (strcmp(s.s[i], t.s[i])) return false;
    return true;
}

void move(const node &s, int u, int v, bool w1, bool w2, int m, int n, int t, node &e) {
    e = s; e.s[u][n-t] = 0;
    if (w1) {
        for (int j=0, k=n-t; j<k; ++j) e.s[u][j] = s.s[u][j+t];
        if (w2) {
            for (int j=t-1, k=j; j>=0; --j) e.s[v][j] = s.s[u][k-j];
            for (int j=0; j<=m; ++j) e.s[v][j+t] = s.s[v][j];
        } else {
            e.s[v][t+m] = 0; for (int j=0; j<t; ++j) e.s[v][j+m] = s.s[u][j];
        }
    } else if (w2) {
        for (int j=0, k=n-t; j<t; ++j) e.s[v][j] = s.s[u][j+k];
        for (int j=0; j<=m; ++j) e.s[v][j+t] = s.s[v][j];
    } else {
        e.s[v][t+m] = 0; for (int j=0, k=n-1; j<t; ++j) e.s[v][j+m] = s.s[u][k-j];
    }
}

int solve() {
    for (int i=0; i<x; ++i) c[i] = 0;
    while (y--) {
        int u, v; char d, e; cin >> u >> d >> v >> e;
        g[u][c[u]++] = {d == 'W', e=='W', v}; g[v][c[v]++] = {e=='W', d=='W', u};
    }
    for (int i=0; i<x; ++i) {
        cin >> s.s[i];
        if (s.s[i][0] == '-') s.s[i][0] = 0;
    }
    for (int i=0; i<x; ++i) {
        cin >> t.s[i];
        if (t.s[i][0] == '-') t.s[i][0] = 0;
    }
    set<node> v1; v1.insert(q[0] = s);
    for (int h=0, d=1, t0=1, t1=1; d<4;) {
        for (int u=0; u<x; ++u) {
            int n = strlen(q[h].s[u]);
            if (n == 0) continue;
            for (int i=0; i<c[u]; ++i) {
                int v = g[u][i].v, m = strlen(q[h].s[v]);
                for (int t=1; t<=n; ++t) {
                    move(q[h], u, v, g[u][i].w1, g[u][i].w2, m, n, t, s);
                    if (check(s)) return d;
                    if (!v1.count(s)) v1.insert(s), q[t1++] = s;
                }
            }
        }
        if (++h == t0) t0 = t1, ++d;
    }
    set<node> v2; v2.insert(q[0] = t);
    for (int h=0, d=1, t0=1, t1=1; d<4;) {
        for (int u=0; u<x; ++u) {
            int n = strlen(q[h].s[u]);
            if (n == 0) continue;
            for (int i=0; i<c[u]; ++i) {
                int v = g[u][i].v, m = strlen(q[h].s[v]);
                for (int t=1; t<=n; ++t) {
                    move(q[h], u, v, g[u][i].w1, g[u][i].w2, m, n, t, s);
                    if (v1.count(s)) return 3+d;
                    if (!v2.count(s)) v2.insert(s), q[t1++] = s;
                }
            }
        }
        if (++h == t0) t0 = t1, ++d;
    }
    return 6;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> x >> y && x) cout << solve() << endl;
    return 0;
}