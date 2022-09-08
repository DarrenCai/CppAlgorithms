/**
 * UVa11600
 * 消灭妖怪
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <set>
using namespace std;

#define N 35
struct node {
    short a[N], n, k; long double d;
    bool operator< (const node& rhs) const {
        if (n != rhs.n) return n < rhs.n;
        for (int i=0; i<n; ++i) if (a[i] != rhs.a[i]) return a[i] < rhs.a[i];
        return k < rhs.k;
    }
};
short fa[N], c[N], n, m; set<node> s;

short find(short x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

long double dp(node& t) {
    set<node>::iterator it = s.find(t);
    if (it != s.end()) return it->d;
    t.d = n - 1.;
    for (short i=0; i<t.n; ++i) if (i != t.k) {
        node t1; t1.n = 0;
        for (short j=0; j<t.n; ++j) if (j!=i && j!=t.k) t1.a[t1.n++] = t.a[j];
        short v = t.a[i]+t.a[t.k];
        t1.k = lower_bound(t1.a, t1.a+t1.n, v) - t1.a;
        for (short j=t1.n++; j>t1.k; --j) t1.a[j] = t1.a[j-1];
        t1.a[t1.k] = v;
        t.d += t.a[i] * dp(t1);
    }
    t.d /= n - t.a[t.k];
    s.insert(t);
    return t.d;
}

void solve(int kase) {
    cin >> n >> m;
    node t; t.a[0] = n; t.n = 1; t.k = 0; t.d = .0;
    s.clear(); s.insert(t);
    for (short i=1; i<=n; ++i) c[fa[i] = i] = 0;
    while (m--) {
        int u, v; cin >> u >> v;
        fa[find(u)] = find(v);
    }
    for (short i=1; i<=n; ++i) ++c[find(i)];
    t.n = 0;
    for (short i=1; i<=n; ++i) if (fa[i] == i) t.a[t.n++] = c[i];
    sort(t.a, t.a+t.n);
    t.k = lower_bound(t.a, t.a+t.n, c[fa[1]]) - t.a;
    cout << "Case " << kase << ": " << dp(t) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(6);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) solve(kase);
    return 0;
}