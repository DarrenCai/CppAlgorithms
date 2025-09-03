/**
 * UVa1472/LA4980
 * 魔法师的帽子
 * CERC 2010
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 100010
long long x[N], y[N], *px; int a[N], n, c; bool w[N], v[N];

bool cmp(int i, int j) {
    return px[i] < px[j];
}

struct {
    long long x[N], y[N], d[N]; int ls[N], rs[N], s[N], p[N], q[N], f[N], t;
    void build(int& o, int l, int r) {
        if (!o) o = ++t, ls[o] = rs[o] = s[o] = 0;
        if (l < r) {
            int u = r;
            for (int i=l; i<r; ++i) if (y[a[i]] < y[a[u]]) u = i;
            int k = a[u]; for (int i=u; i<r; ++i) a[i] = a[i+1]; a[r] = k;
            u = (l+r-1)>>1; while (u+1 < r & x[a[u+1]] == x[a[u]]) ++u;
            d[o] = x[a[u]]; build(ls[o], l, u);
            if (u+1 < r) build(rs[o], u+1, r-1);
            p[o] = k; f[ls[o]] = f[rs[o]] = q[k] = o; s[o] = r-l+1;
        } else p[o] = a[l], q[a[l]] = o, s[o] = 1;
    }
    void build() {
        int o = s[0] = t = 0; px = x; sort(a, a+n, cmp); build(o, 0, n-1);
    }
    int query(int o, int i) {
        if (!s[o] || y[p[o]] > y[i]) return 0;
        int cnt = 0;
        if (p[o] != i && v[p[o]] && x[p[o]] <= x[i]) a[c++] = p[o], v[p[o]] = false, ++cnt;
        if (ls[o]) cnt += query(ls[o], i);
        if (rs[o] && x[i] > d[o]) cnt += query(rs[o], i);
        s[o] -= cnt;
        return cnt;
    }
    void remove(int i) {
        for (int o = q[i]; o; o = f[o]) --s[o];
    }
} t1, t2;

void solve() {
    cin >> n;
    for (int i=0; i<n; ++i) {
        char c; cin >> x[i] >> y[i] >> c; w[i] = c == 'W'; a[i] = i; v[i] = true;
        t1.x[i] = y[i]-x[i]; t1.y[i] = y[i]+x[i]; t2.x[i] = y[i]-2*x[i]; t2.y[i] = y[i]+2*x[i];
    }
    t1.build(); t2.build();
    for (int i=0, ans = 0; i<n; ++i) 
        if (v[i]) {
            if (w[i]) {
                c = 0; t1.query(1, i);
                while (c--) {
                    if (a[c] < i) --ans;
                    t2.remove(a[c]);
                }
            } else {
                c = 0; t2.query(1, i);
                while (c--) {
                    if (a[c] < i) --ans;
                    t1.remove(a[c]);
                }
            }
            cout << (ans += 1) << endl;
        } else cout << "FAIL" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}