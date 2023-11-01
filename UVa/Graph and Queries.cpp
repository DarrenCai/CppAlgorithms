/**
 * UVa1479/LA5031
 * 图询问
 * Tianjin 2010
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define M 60010
#define N 20005
#define T 460100
int u[M], v[M], f[N], w[N], x[T], y[T], m, n, t, kase = 0; char c[T], ch; bool del[M];

struct node {
    node *ch[2]; int r, v, s;
    node(int x=0):ch{NULL, NULL}, r(rand()), v(x), s(1) {}
    bool operator < (const node& rhs) const {
        return r < rhs.r;
    }
    int cmp(int x) const {
        if (x == v) return -1;
        return x < v ? 0 : 1;
    }
    void maintain() {
        s = 1;
        if(ch[0]) s += ch[0]->s;
        if(ch[1]) s += ch[1]->s;
    }
} s[N], *p[N];

void rotate(node* &o, int d) {
    node* k = o->ch[d^1]; o->ch[d^1] = k->ch[d]; k->ch[d] = o;
    o->maintain(); k->maintain(); o = k;
}

void insert(node* &o, node* t) {
    if (o) {
        if (t->ch[0]) insert(o, t->ch[0]), t->ch[0] = NULL;
        if (t->ch[1]) insert(o, t->ch[1]), t->ch[1] = NULL;
        int d = t->v >= o->v;
        insert(o->ch[d], t);
        if (o->ch[d] > o) rotate(o, d^1);
    } else o = t;
    o->maintain();
}

node* remove(node* &o, int x) {
    int d = o->cmp(x); node *p = NULL;
    if (d == -1) {
        if (o->ch[0] && o->ch[1]) {
            int d2 = o->ch[1] < o->ch[0];
            rotate(o, d2); p = remove(o->ch[d2], x);
        } else p = o, o = o->ch[1] ? o->ch[1] : o->ch[0];
    } else p = remove(o->ch[o->cmp(x)], x);
    if (o) o->maintain();
    return p;
}

int kth(const node* o, int k) {
    if (!o) return 0;
    int l = o->ch[0] ? o->ch[0]->s : 0, r = o->ch[1] ? 1 + o->ch[1]->s : 1;
    return k==r ? o->v : (k<r ? kth(o->ch[1], k) : kth(o->ch[0], k-r));
}

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

void solve() {
    for (int i=1; i<=n; ++i) cin >> w[i], s[i].ch[0] = s[i].ch[1] = NULL, f[i] = i, p[i] = s+i;
    for (int i=1; i<=m; ++i) cin >> u[i] >> v[i], del[i] = false;
    t = 0;
    while (cin >> ch && ch != 'E') {
        cin >> x[t];
        if (ch == 'D') del[x[t]] = true;
        else {
            cin >> y[t];
            if (ch == 'C') f[0] = w[x[t]], w[x[t]] = y[t], y[t] = f[0];
        }
        c[t++] = ch;
    }
    for (int i=1; i<=n; ++i) s[i].v = w[i];
    for (int i=1; i<=m; ++i) if (!del[i]) {
        int x = find(u[i]), y = find(v[i]);
        if (x == y) continue;
        if (p[x]->s < p[y]->s) insert(p[y], p[x]), f[x] = y;
        else insert(p[x], p[y]), f[y] = x;
    }
    double sum = 0.; int cnt = 0;
    for (int i=t-1; i>=0; --i) {
        if (c[i] == 'D') {
            int y = find(u[x[i]]), z = find(v[x[i]]);
            if (y == z) continue;
            if (p[z]->s < p[y]->s) insert(p[y], p[z]), f[z] = y;
            else insert(p[z], p[y]), f[y] = z;
        } else if (c[i] == 'C') {
            node *r = p[find(x[i])], *q = remove(r, w[x[i]]);
            w[x[i]] = q->v = y[i]; q->ch[0] = q->ch[1] = NULL; insert(r, q);
        } else sum += kth(p[find(x[i])], y[i]), ++cnt;
    }
    cout << "Case " << ++kase << ": " << sum/max(cnt, 1) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(6);
    while (cin>>n>>m && n) solve();
    return 0;
}