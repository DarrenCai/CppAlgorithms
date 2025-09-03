/**
 * UVa1383/LA3699
 * 永远的和谐
 * Shanghai 2006
 */

#include <iostream>
using namespace std;

#define M 500000
#define N 40010
#define T 20*N
struct node {int v, i;} s[T]; int lc[T], rc[T], x[N], m, n, t, kase = 0;

void update(int& o, int l, int r, int x, int i) {
    if (!o) o = ++t, lc[o] = rc[o] = 0;
    if (l < r) {
        int m = (l+r)>>1;
        x <= m ? update(lc[o], l, m, x, i) : update(rc[o], m+1, r, x, i);
        s[o] = s[lc[o]].v < s[rc[o]].v ? s[lc[o]] : s[rc[o]];
    } else s[o] = {x, i};
}

node query(int o, int l, int r, int x1, int x2) {
    if (l >= x1 && r <= x2) return s[o];
    int m = (l+r)>>1; node a = s[0];
    if (x1 <= m && lc[o]) {
        node b = query(lc[o], l, m, x1, x2);
        if (b.v < a.v) a = b;
    }
    if (x2 > m && rc[o]) {
        node b = query(rc[o], m+1, r, x1, x2);
        if (b.v < a.v) a = b;
    }
    return a;
}

int query(int y) {
    if (!m) return -1;
    int r = M, ans = 0;
    if (y < 5000) for (int i=m; i>0; --i) {
        int a = x[i] % y;
        if (!a) return i;
        if (a < r) r = a, ans = i;
    } else for (int i=0; i<=M; i+=y) {
        node a = query(1, 0, M, i, i+y-1);
        if (a.v-i < r || (a.v-i == r && a.i > ans)) r = a.v-i, ans = a.i;
    }
    return ans;
}

void solve() {
    if (kase) cout << endl;
    cout << "Case " << ++kase << ':' << endl;
    for (int i = m = lc[1] = rc[1] = 0, r = t= 1; i<n; ++i) {
        char c; int y; cin >> c>> y;
        if (c == 'A') cout << query(y) << endl;
        else x[++m] = y, update(r = 1, 0, M, y, m);
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    s[0] = {10*M, 0};
    while (cin >> n && n) solve();
    return 0;
}