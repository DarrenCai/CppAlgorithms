/**
 * UVa1480/LA5034
 * Tianjin 2010
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 103000
#define T 18*N
struct {int e, s, t, x;} op[2*N]; int a[N], st[N], lc[T], rc[T], s[T], m, n, t, kase = 0; char e[8];

void update(int& o, int pre, int l, int r, int x) {
    int m = (l+r)>>1; o = ++t; lc[o] = lc[pre]; rc[o] = rc[pre]; s[o] = s[pre]+1;
    if (l == r) return;
    x <= m ? update(lc[o], lc[pre], l, m, x) : update(rc[o], rc[pre], m+1, r, x);
}

int kth(int o, int pre, int l, int r, int k) {
    if (l == r) return a[l];
    int c = s[lc[o]] - s[lc[pre]], m = (l+r) >> 1;
    return k <= c ? kth(lc[o], lc[pre], l, m, k) : kth(rc[o], rc[pre], m+1, r, k-c);
}

int rnk(int o, int l, int r, int x) {
    if (l == r) return 1;
    int m = (l+r)>>1;
    return x <= m ? rnk(lc[o], l, m, x) : s[lc[o]] + rnk(rc[o], m+1, r, x);
}

void solve() {
    for (int i=m=t=0; i<n; ++i) {
        cin >> e; op[i].e = e[0]=='I' ? 0 : e[6]-'0';
        op[i].e == 1 ? cin >> op[i].s >> op[i].t >> op[i].x : cin >> op[i].x;
        if (op[i].e == 0) a[++m] = op[i].x;
    }
    sort(a+1, a+m+1);
    long long q1 = 0, q2 = 0, q3 = 0;
    for (int i=0, c=0; i<n; ++i) {
        if (op[i].e == 0) ++c, update(st[c], st[c-1], 1, m, lower_bound(a+1, a+m+1, op[i].x)-a);
        else if (op[i].e == 1) q1 += kth(st[op[i].t], st[op[i].s-1], 1, m, op[i].x);
        else if (op[i].e == 2) q2 += rnk(st[c], 1, m, lower_bound(a+1, a+m+1, op[i].x)-a);
        else q3 += kth(st[c], st[0], 1, m, op[i].x);
    }
    cout << "Case " << ++kase << ':' << endl << q1 << endl << q2 << endl << q3 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    st[0] = lc[0] = rc[0] = s[0] = 0;
    while (cin >> n) solve();
    return 0;
}