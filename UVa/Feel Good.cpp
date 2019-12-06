/**
 * UVa1619
 * 感觉不错
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 100010
#define max(a, b) (a>b ? a:b)

int a[N], b[N], n, l, r; long long s[N]={0}, g;
bool cmp(int i, int j) {
    return a[i] < a[j] || (a[i] == a[j] && i<j);
}

struct range{
    int a, b;
    range(int a, int b): a(a), b(b) {}
};
struct node {
    int key, height;
    node *left, *right;
    node(int key, node *l, node *r): key(key), height(0), left(l), right(r) {}
};

class AVLTree {
private:
    node* root;
    int height(node* p) {
        return p == NULL ? 0 : p->height;
    }
    void destroy(node* &p) {
        if (p==NULL) return;
        if (p->left != NULL) destroy(p->left);
        if (p->right != NULL) destroy(p->right);
        delete p;
    }
    node* insert(node* &p, int key) {
        if (p == NULL) {
            p = new node(key, NULL, NULL);
        } else if (key < p->key) {
            p->left = insert(p->left, key);
            if (height(p->left) - height(p->right) == 2) {
                if (key < p->left->key) p = llRotate(p);
                else p = lrRotate(p);
            }
        } else if (key > p->key) {
            p->right = insert(p->right, key);
            if (height(p->right) - height(p->left) == 2) {
                if (key > p->right->key) p = rrRotate(p);
                else p = rlRotate(p);
            }
        }
        p->height = max(height(p->left), height(p->right)) + 1;
        return p;
    }
    node* llRotate(node* p) {
        node* q = p->left;
        p->left = q->right;
        q->right = p;
        p->height = max(height(p->left), height(p->right)) + 1;
        q->height = max(height(q->left), p->height) + 1;
        return q;
    }
    node* rrRotate(node* p) {
        node* q = p->right;
        p->right = q->left;
        q->left = p;
        p->height = max(height(p->left), height(p->right)) + 1;
        q->height = max(height(q->right), p->height) + 1;
        return q;
    }
    node* lrRotate(node* p) {
        p->left = rrRotate(p->left);
        return llRotate(p);
    }
    node* rlRotate(node* p) {
        p->right = llRotate(p->right);
        return rrRotate(p);
    }
public:
    AVLTree(): root(NULL) {}
    ~AVLTree() {
        destroy(root);
    }
    void insert(int key) {
        insert(root, key);
    }
    range search(int key) const {
        range ret(1, n);
        for (node* x = root; x != NULL && x->key != key;) {
            if (key < x->key) {
                ret.b = x->key - 1;
                x = x->left;
            } else {
                ret.a = x->key + 1;
                x = x->right;
            }
        }
        return ret;
    }
};

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    bool first = true;
    while (cin >> n) {
        for (int i=1; i<=n; ++i) cin >> a[i], s[i] = s[i-1] + a[i], b[i] = i;
        sort(b+1, b+1+n, cmp);
        g = -1;
        for (int i=1; i<=n; ++i) {
            long long v = (long long)a[i]*a[i];
            if (v > g) g=v, l=i, r=i;
        }
        AVLTree t;
        for (int i=1; i<=n; ++i) {
            range ret = t.search(b[i]);
            long long v = (s[ret.b] - s[ret.a-1]) * a[b[i]];
            if (v > g || (v==g && (r-l > ret.b-ret.a || (r-l==ret.b-ret.a && l > ret.a)))) g = v, l = ret.a, r = ret.b;
            t.insert(b[i]);
        }
        if (!first) cout << endl;
        cout << g << endl << l << ' ' << r << endl;
        first = false;
    }
}