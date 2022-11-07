/**
 * UVa1390/LA3710
 * 互联
 * NEERC 2006
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
using namespace std;

#define N 32

struct state {
    struct {short c, n;} a[N]; short n;
    bool operator< (const state& rhs) const {
        if (n != rhs.n) return n < rhs.n;
        for (short i=0; i<n; ++i) {
            if (a[i].c != rhs.a[i].c) return a[i].c < rhs.a[i].c;
            if (a[i].n != rhs.a[i].n) return a[i].n < rhs.a[i].n;
        }
        return false;
    }
};

short a[N], c[N], p[N], m, n, t; map<state, double> d;

short find(short x) {
    return p[x] = x==p[x] ? x : find(p[x]);
}

double dp(const state& s) {
    if (s.a[0].c == n) return 0.;
    if (d.count(s)) return d[s];
    double v = 0.; short c = 0;
    for (short i=0; i<s.n; ++i) {
        c += s.a[i].n*s.a[i].c*(s.a[i].c-1);
        if (s.a[i].n > 1) {
            state e; e.n = 0; short cc = s.a[i].c << 1;
            for (short j=0; j<i; ++j) e.a[e.n++] = s.a[j];
            if (s.a[i].n > 2) e.a[e.n].c = s.a[i].c, e.a[e.n++].n = s.a[i].n-2;
            for (short j=i+1; j<s.n; ++j) {
                if (cc && s.a[j].c > cc) e.a[e.n].c = cc, e.a[e.n++].n = 1, e.a[e.n++] = s.a[j], cc = 0;
                else if (cc && s.a[j].c == cc) e.a[e.n].c = cc, e.a[e.n++].n = s.a[j].n+1, cc = 0;
                else e.a[e.n++] = s.a[j];
            }
            if (cc) e.a[e.n].c = cc, e.a[e.n++].n = 1;
            v += dp(e) * s.a[i].n * (s.a[i].n-1) * s.a[i].c * s.a[i].c;
        }
        for (short j=i+1; j<s.n; ++j) {
            state e; e.n = 0; short cc = s.a[i].c + s.a[j].c;
            for (short k=0; k<i; ++k) e.a[e.n++] = s.a[k];
            if (s.a[i].n > 1) e.a[e.n].c = s.a[i].c, e.a[e.n++].n = s.a[i].n-1;
            for (short k=i+1; k<j; ++k) e.a[e.n++] = s.a[k];
            if (s.a[j].n > 1) e.a[e.n].c = s.a[j].c, e.a[e.n++].n = s.a[j].n-1;
            for (short k=j+1; k<s.n; ++k) {
                if (cc && s.a[k].c > cc) e.a[e.n].c = cc, e.a[e.n++].n = 1, e.a[e.n++] = s.a[k], cc = 0;
                else if (cc && s.a[k].c == cc) e.a[e.n].c = cc, e.a[e.n++].n = s.a[k].n+1, cc = 0;
                else e.a[e.n++] = s.a[k];
            }
            if (cc) e.a[e.n].c = cc, e.a[e.n++].n = 1;
            v += dp(e) * s.a[i].n * s.a[j].n * s.a[i].c * s.a[j].c * 2;
        }
    }
    return d[s] = (v + t) / (t - c);
}

double solve() {
    state s; t = n*(n-1); d.clear();
    for (short i=1; i<=n; ++i) c[p[i] = i] = 1;
    while (m--) {
        short u, v; cin >> u >> v;
        u = find(u); v = find(v);
        if (u != v) p[u] = v, c[v] += c[u];
    }
    for (short i=1; i<=n; ++i) if (i == p[i]) a[++m] = c[i];
    sort(a, a+m+1);
    s.a[0].c = a[0]; s.a[0].n = 1; s.n = 1;
    for (short i=1; i<=m; ++i) {
        if (a[i] != a[i-1]) s.a[s.n].c = a[i], s.a[s.n++].n = 1;
        else ++s.a[s.n-1].n;
    }
    return dp(s);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(6);
    while (cin>>n>>m) cout << solve() << endl;
    return 0;
}