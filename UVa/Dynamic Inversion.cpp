/**
 * UVa11990
 * “动态”逆序对
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 200100
int a[N], p[N], c[N], e[N], m, n, t; long long s;
struct node {int v, d; node *l, *r;} q[N*18], *h[N];

node* build(int a, int b) {
    if (a >= b) return NULL;
    node *r = q + t++; int m = (a+b)>>1; *r = {e[m], 0, build(a, m), build(m+1, b)};
    return r;
}

int query(const node *p, int s, int v) {
    if (!p) return 0;
    if (p->v >= v) return query(p->l, s>>1, v);
    int ld = (p->l ? p->l->d : 0), c = p->d - ld - (p->r ? p->r->d : 0);
    return (s>>1) - ld + 1-c + query(p->r, s-1 - (s>>1), v);
}

int query(int x) {
    int a = x-1, b = 0, e = 0;
    for (int i=x; i; i -= i&-i) a -= c[i];
    for (int i=p[x]-1; i; i -= i&-i) b += (i&-i) - h[i]->d, e += query(h[i], i&-i, x);
    return b-e + a-e;
}

void remove(node *p, int v) {
    p->d ++;
    if (p->l && p->v > v) remove(p->l, v);
    if (p->r && v > p->v) remove(p->r, v);
}

void solve() {
    memset(c, s = t = 0, sizeof(c));
    for (int i=1; i<=n; ++i) {
        cin >> a[i]; p[a[i]] = i;
        for (int x = a[i]+1; x<=n; x += x&-x) s += c[x];
        for (int x = a[i]; x; x -= x&-x) ++c[x];
        int cc = i&-i;
        for (int j=i-cc+1, k=0; j<=i; ++j) e[k++] = a[j];
        sort(e, e+cc);
        h[i] = q + t++; *h[i] = {e[cc>>1], 0, build(0, cc>>1), build((cc>>1)+1, cc)};
    }
    memset(c, 0, sizeof(c));
    while (m--) {
        int x; cin >> x;
        cout << s << endl;
        s -= query(x);
        for (int i=x; i<=n; i += i&-i) ++c[i];
        for (int i=p[x]; i<=n; i += i&-i) remove(h[i], x);
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) solve();
    return 0;
}