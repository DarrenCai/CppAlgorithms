/**
 * UVa1375/LA3623
 * 给孩子起名
 * Asia Japan 2006 in Yokohama
 */

#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

#define M 520
#define L 22
struct node {
    short a, c;
    node(short a, short c):a(a),c(c) {}
    bool operator< (const node& rhs) const {
        return a < rhs.a || (a == rhs.a && c < rhs.c);
    }
};
set<node> u[M]; map<string, short> ss; string d[M][L], e(""); struct {short a, b, c;} r[M]; short c, t, n, l, ll;
struct cmp {
    bool operator() (short a, short b) const {
        return d[a][ll] < d[b][ll] || (d[a][ll] == d[b][ll] && a<b);
    }
};

short id(const string& s) {
    if (ss.count(s)) return ss[s];
    for (short i=0; i<L; ++i) d[t][i] = "~";
    u[t].clear();
    return ss[s] = t++;
}

void solve() {
    ss.clear(); u[c = 0].clear(); t = 1;
    d[ss[e] = 0][0] = e; for (short i=1; i<L; ++i) d[0][i] = "~";
    for (short i=0; i<n; ++i) {
        string s, x(e), y(e); cin >> s; short l = s.size(), cc = 0;
        if (l == 2) {
            d[id(s[0]+e)][0] = e; continue;
        }
        for (short j=l-1, a=0; j>1; --j) {
            if (s[j] <= 'Z') {
                if (a > 0) {
                    d[id(x)][a] = x;
                    if (y.size() > 0) {
                        r[c].a = id(x); r[c].b = id(y);
                        short d = id(x+y);
                        if (cc == x.size()) u[r[c].a].insert(node(r[c].b, d));
                        r[c++].c = d;
                    }
                    y = x+y;
                }
                if (j > 2) {
                    if (y.size() > 0) {
                        r[c].a = id(s[j]+e); r[c].b = id(y);
                        short d = id(y = s[j]+y);
                        u[r[c].b].insert(node(r[c].a, d));
                        if (cc == 0) u[r[c].a].insert(node(r[c].b, d));
                        r[c++].c = d;
                    } else y = s[j];
                }
                x = e; a = 0;
            } else x = s[j] + x, ++a, ++cc;
        }
        if (x.size() > 0) {
            d[id(x)][x.size()] = x;
            if (y.size() == 0) {
                string& r = d[id(s[0]+e)][l-2]; r = min(r, x);
            } else {
                r[c].a = id(x); r[c].b = id(y);
                short d = id(s[0]+e);
                if (cc == x.size()) u[r[c].a].insert(node(r[c].b, d));
                r[c++].c = d;
            }
        } else {
            r[c].a = id(s[2]+e); r[c].b = id(y);
            short d = id(s[0]+e);
            u[r[c].b].insert(node(r[c].a, d));
            if (cc == 0) u[r[c].a].insert(node(r[c].b, d));
            r[c++].c = d;
        }
    }
    for (short ll=0; ll<=l; ++ll) {
        for (short i=0; i<c; ++i) {
            short a = r[i].a, b = r[i].b, c = r[i].c;
            for (short j=1; j<ll; ++j) if (d[a][j]<"~" && d[b][ll-j]<"~") d[c][ll] = min(d[c][ll], d[a][j]+d[b][ll-j]);
        }
        set<short, cmp> q;
        for (short i=0; i<t; ++i) if (d[i][ll] < "~") q.insert(i);
        while (!q.empty()) {
            set<short, cmp>::iterator it = q.begin(); short i = *it; q.erase(it);
            for (set<node>::iterator it=u[i].begin(); it!=u[i].end(); ++it) {
                short a = it->a, c = it->c;
                if (d[a][0]==e && d[i][ll]<d[c][ll]) d[c][ll] = d[i][ll], q.erase(c), q.insert(c);
            }
        }
    }
    const string& ans = d[id("S")][l];
    cout << (ans == "~" ? "-" : ans) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n>>l && n) solve();
    return 0;
}