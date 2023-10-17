/**
 * UVa1400/LA3938
 * 动态最大连续和
 * Nanjing 2007
 */

#include <iostream>
using namespace std;

int m, n, ql, qr, kase = 0; long long s[1<<19], x;

struct intv {
    int l, r;
    intv(int l=0, int r=0): l(l), r(r) {}
    bool operator< (const intv &rhs) const {
        long long x = s[r] - s[l-1], y = s[rhs.r] - s[rhs.l-1];
        return x!=y ? x<y : (l!=rhs.l ? l>rhs.l : r>rhs.r);
    }
};
struct node {intv l, r, a;} d[1<<20];

node query(int o, int l, int r) {
    if (l>=ql && r<=qr) return d[o];
    int m = (l + r) >> 1;
    if (ql > m) return query(2*o+1, m+1, r);
    if (qr <= m) return query(2*o, l, m);
    node x = query(2*o, l, m), y = query(2*o+1, m+1, r), ans;
    ans.a = max(max(x.a, y.a), intv(x.r.l, y.l.r));
    ans.l = max(x.l, intv(l, y.l.r));
    ans.r = max(y.r, intv(x.r.l, r));
    return ans;
}

const node& build(int o, int l, int r) {
    if (l == r) {
        d[o].l = d[o].r = d[o].a = intv(l, l);
    } else {
        int m = (l + r) >> 1;
        const node &x = build(2*o, l, m), &y = build(2*o+1, m+1, r);
        d[o].a = max(max(x.a, y.a), intv(x.r.l, y.l.r));
        d[o].l = max(x.l, intv(l, y.l.r));
        d[o].r = max(y.r, intv(x.r.l, r));
    }
    return d[o];
}

void solve() {
    cout << "Case " << ++kase << ':' << endl;
    for (int i=1; i<=n; ++i) cin >> x, s[i] = s[i-1]+x;
    build(1, 1, n);
    while (m--) {
        cin >> ql >> qr;
        intv ans = query(1, 1, n).a;
        cout << ans.l << ' ' << ans.r << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    s[0] = 0;
    while (cin >> n >> m) solve();
    return 0;
}