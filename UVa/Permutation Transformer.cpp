/**
 * UVa11922
 * 排列变换
 */

#include <iostream>
using namespace std;

#define N 100050

struct node {
    node *ch[2]; int v, s = 0, flip = 0;
    int cmp(int k) const {
        int d = k - (ch[0] ? ch[0]->s : 0);
        if (d == 1) return -1;
        return d > 0;
    }
    void maintain() {
        s = ch[0]->s + ch[1]->s + 1;
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

int m, n;

node* build(int x, int cl, int cr) {
    s[x].v = x; s[x].s = cl+cr+1; s[x].flip = 0;
    s[x].ch[0] = cl ? build(x-1-(cl>>1), cl-1-(cl>>1), cl>>1) : null;
    s[x].ch[1] = cr ? build(x+cr-(cr>>1), cr-1-(cr>>1), cr>>1) : null;
    return s+x;
}

void print(node* o) {
    o->pushdown();
    if (o->ch[0] != null) print(o->ch[0]);
    if (o->v) cout << o->v << endl;
    if (o->ch[1] != null) print(o->ch[1]);
}

void solve() {
    node *root = build(n-(n>>1), n-(n>>1), n>>1);
    while (m--) {
        int a, b; cin >> a >> b;
        node *o, *l, *r, *mid;
        split(root, a, l, o);
        split(o, b-a+1, mid, r);
        mid->flip ^= 1;
        root = merge(merge(l, r), mid);
    }
    print(root);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    solve();
    return 0;
}