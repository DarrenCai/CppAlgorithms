/**
 * UVa11996
 * 魔法珠宝
 */

#include <iostream>
using namespace std;

#define N 400200
unsigned int m, n, pow[N], x = 123; char t[N] = "0";

struct node {
    node *ch[2]; unsigned int v, s = 0, flip = 0, h = 0, rh = 0;
    int cmp(int k) const {
        int d = k - (ch[0] ? ch[0]->s : 0);
        if (d == 1) return -1;
        return d > 0;
    }
    unsigned int get_h() {
        return flip ? rh : h;
    }
    unsigned int get_rh() {
        return flip ? h : rh;
    }
    void maintain() {
        s = ch[0]->s + ch[1]->s + 1;
        h = ch[0]->get_h() + v*pow[ch[0]->s] + ch[1]->get_h()*pow[ch[0]->s+1];
        rh = ch[1]->get_rh() + v*pow[ch[1]->s] + ch[0]->get_rh()*pow[ch[1]->s+1];
    }
    void pushdown() {
        if (flip) {
            flip = 0;
            node *p = ch[0]; ch[0] = ch[1]; ch[1] = p;
            ch[0]->flip ^= 1; ch[1]->flip ^= 1;
        }
    }
} *null = new node(), s[N];

void rotate(node*& o, int d) {
    node* k = o->ch[d^1]; o->ch[d^1] = k->ch[d]; k->ch[d] = o;
    o->maintain(); k->maintain(); o = k;
}

void splay(node*& o, int k) {
    o->pushdown();
    int d = o->cmp(k);
    if (d == -1) return;
    if (d) k -= o->ch[0]->s + 1;
    node* p = o->ch[d];
    p->pushdown();
    int d2 = p->cmp(k);
    if (d2 != -1) {
        splay(p->ch[d2], d2 ? k - p->ch[0]->s - 1 : k);
        if (d == d2) rotate(o, d^1);
        else rotate(o->ch[d], d);
    }
    rotate(o, d^1);
}

node* merge(node* left, node* right) {
    splay(left, left->s);
    left->ch[1] = right;
    left->maintain();
    return left;
}

void split(node* o, int k, node*& left, node*& right) {
    splay(o, k);
    left = o;
    right = o->ch[1];
    o->ch[1] = null;
    left->maintain();
}

node* build(int i, int cl, int cr) {
    s[i].v = t[i]-'0'; s[i].flip = 0;
    s[i].ch[0] = cl ? build(i-1-(cl>>1), cl-1-(cl>>1), cl>>1) : null;
    s[i].ch[1] = cr ? build(i+cr-(cr>>1), cr-1-(cr>>1), cr>>1) : null;
    s[i].maintain();
    return s+i;
}

int lcp(node*& root, int p1, int p2) {
    int low = 0, high = root->s - p2;
    while (low <= high) {
        int m = (low + high) >> 1;
        if (m == 0) {
            low = 1; continue;
        }
        node *l, *o, *mid, *r;
        split(root, p1, l, o); split(o, m, mid, r);
        unsigned int h1 = mid->get_h();
        root = merge(merge(l, mid), r);
        split(root, p2, l, o); split(o, m, mid, r);
        unsigned int h2 = mid->get_h();
        root = merge(merge(l, mid), r);
        h1 == h2 ? low = m+1 : high = m-1;
    }
    return high;
}

void solve() {
    cin >> t+1;
    node *root = build(n-(n>>1), n-(n>>1), n>>1);
    while (m--) {
        int x, p, p2; cin >> x >> p;
        if (x == 1) {
            node *l, *r, *y = s + ++n;
            cin >> y->v; y->h = y->rh = y->v; y->s = 1; y->flip = 0; y->ch[0] = y->ch[1] = null;
            split(root, ++p, l, r); root = merge(merge(l, y), r);
        } else if (x == 2) {
            node *l, *r;
            split(root, ++p, l, r); l = l->ch[0]; root = merge(l,r);
        } else if (x == 3) {
            cin >> p2;
            node *l, *o, *mid, *r;
            split(root, p, l, o); split(o, p2+1-p, mid, r); mid->flip ^= 1; root = merge(merge(l, mid), r);
        } else cin >> p2, cout << lcp(root, p, p2) << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    pow[0] = 1; for (int i=1; i<N; ++i) pow[i] = x*pow[i-1];
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) solve();
    return 0;
}