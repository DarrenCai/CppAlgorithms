/**
 * UVa1455/LA4730
 * 王国
 * Seoul 2009
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 100100
struct node {int c, s;} t[1<<21];
int f[N], y1[N], y2[N], c[N], x, m, n, Y = (1<<20)-1; double y; char s[5];

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

void op(int o, int l, int r, int p, bool add = false) {
    if (y1[p] == y2[p]) return;
    if (l>=y1[p] && r<y2[p]) {
        add ? (++t[o].c, t[o].s += c[p]) : (--t[o].c, t[o].s -= c[p]);
    } else {
        int m = (l+r) >> 1, lc = o << 1, rc = lc + 1;
        t[lc].c += t[o].c; t[lc].s += t[o].s; t[rc].c += t[o].c; t[rc].s += t[o].s; t[o].c = t[o].s = 0;
        if (y1[p] <= m) op(lc, l, m, p, add);
        if (y2[p] > m+1) op(rc, m+1, r, p, add);
    }
}

const node& query(int o, int l, int r) {
    if (l < r) {
        int m = (l+r) >> 1, lc = o << 1, rc = lc + 1;
        t[lc].c += t[o].c; t[lc].s += t[o].s; t[rc].c += t[o].c; t[rc].s += t[o].s; t[o].c = t[o].s = 0;
        return x > m ? query(rc, m+1, r) : query(lc, l, m);
    } else return t[o];
}

void solve() {
    cin >> n;
    for (int i=0; i<n; ++i) c[f[i] = i] = 1, cin >> x >> y1[i], y2[i] = y1[i];
    cin >> m;
    memset(t, 0, sizeof(t));
    while (m--) {
        cin >> s;
        if (s[0] == 'r') {
            int u, v; cin >> u >> v;
            int x = find(u), y = find(v);
            if (x != y) {
                op(1, 0, Y, x); op(1, 0, Y, y);
                f[x] = y; c[y] += c[x]; y1[y] = min(y1[y], y1[x]); y2[y] = max(y2[y], y2[x]);
                op(1, 0, Y, y, true);
            }
        } else {
            cin >> y; x = y;
            const node& r = query(1, 0, Y);
            cout << r.c << ' ' << r.s << endl;
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}