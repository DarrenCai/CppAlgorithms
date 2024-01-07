/**
 * UVa12419
 * 内存分配
 */

#include <cstdio>
#include <queue>
using namespace std;

#define N 200050
int a[120*N], b[120*N], c[120*N], z[120*N], lc[120*N], rc[120*N], n, g, x; struct {int i, m; long long t;} q[N];

struct node {
    long long t; int s, e;
    bool operator< (const node& rhs) const {
        return t > rhs.t;
    }
} r;

int query(int o, int l, int r, int s) {
    if (s == 0 || a[o] >= s) return l;
    if (c[o] < s) return 0;
    int m = (l+r)>>1, cl = lc[o] ? c[lc[o]] : m-l+1, bl = lc[o] ? b[lc[o]] : m-l+1, cr = rc[o] ? c[rc[o]] : r-m;
    if (cl >= s) return lc[o] ? query(lc[o], l, m, s) : l;
    if (bl + (rc[o] ? a[rc[o]] : r-m) >= s) return m-bl+1;
    return cr >= s ? (rc[o] ? query(rc[o], m+1, r, s) : m+1) : 0;
}

void pushdown(int o, int l, int r) {
    if (z[o] >= 0) {
        a[o] = b[o] = c[o] = z[o] ? 0 : r-l+1;
    } else {
        int m = (l+r)>>1, bl = lc[o] ? b[lc[o]] : m-l+1, ar = rc[o] ? a[rc[o]] : r-m;
        a[o] = lc[o] && a[lc[o]] <= m-l ? a[lc[o]] : m-l+1 + (rc[o] ? a[rc[o]] : r-m);
        b[o] = rc[o] && b[rc[o]] < r-m ? b[rc[o]] : r-m + (lc[o] ? b[lc[o]] : m-l+1);
        c[o] = max(bl+ar, max(lc[o] ? c[lc[o]] : m-l+1, rc[o] ? c[rc[o]] : r-m));
    }
}

void check(int &o, int l, int r) {
    if (o) return;
    o = ++x; a[o] = b[o] = c[o] = r-l+1; z[o] = lc[o] = rc[o] = 0;
}

void occ(int o, int l, int r, int x, int y, bool f) {
    if (x > y) return;
    if (l>=x && r<=y) {
        z[o] = f;
    } else {
        int m = (l+r)>>1; check(lc[o], l, m); check(rc[o], m+1, r);
        if (z[o] >= 0) z[lc[o]] = z[rc[o]] = z[o], z[o] = -1;
        x <= m ? occ(lc[o], l, m, x, y, f) : pushdown(lc[o], l, m);
        y > m ? occ(rc[o], m+1, r, x, y, f) : pushdown(rc[o], m+1, r);
    }
    pushdown(o, l, r);
}

void solve() {
    a[1] = b[1] = c[1] = n; z[x = 1] = lc[1] = rc[1] = 0;
    int m, i = 0, a, head = 0, tail = 0; long long ans = 0, t, p; priority_queue<node> s;
    while (scanf("%lld%d%lld", &t, &m, &p) && (t || m || p) && ++i) {
        while (!s.empty() && s.top().t <= t) {
            for (ans = s.top().t; !s.empty() && s.top().t == ans; s.pop()) occ(1, 1, n, s.top().s, s.top().e, 0);
            while (head < tail) {
                if (!(a = query(1, 1, n, q[head].m))) break;
                if (g) printf("%lld %d %d\n", ans, q[head].i, a-1);
                r.t = ans + q[head].t; r.s = a; r.e = a+q[head++].m-1; occ(1, 1, n, a, r.e, 1); s.push(r);
            }
        }
        if (a = query(1, 1, n, m)) {
            if (g) printf("%lld %d %d\n", t, i, a-1);
            r.t = t + p; r.s = a; r.e = a+m-1; occ(1, 1, n, a, r.e, 1); s.push(r);
        } else q[tail].i = i, q[tail].t = p, q[tail++].m = m;
    }
    while (!s.empty()) {
        for (ans = s.top().t; !s.empty() && s.top().t == ans; s.pop()) occ(1, 1, n, s.top().s, s.top().e, 0);
        while (head < tail) {
            if (!(a = query(1, 1, n, q[head].m))) break;
            if (g) printf("%lld %d %d\n", ans, q[head].i, a-1);
            r.t = ans + q[head].t; r.s = a; r.e = a+q[head++].m-1; occ(1, 1, n, a, r.e, 1); s.push(r);
        }
    }
    printf("%lld\n%d\n\n", ans, tail);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (scanf("%d%d", &n, &g) == 2) solve();
    return 0;
}