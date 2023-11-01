struct node {
    node *ch[2];    //左右子树
    int r;          //随机优先级。数值越大，优先级越高
    int v;          //值
    int s;          //名次树附加域size
    node(int x = 0): ch{NULL, NULL}, r(rand()), v(x), s(1) {}
    bool operator < (const node& rhs) const {       //根据优先级比较结点
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
};

int find(node* o, int x) {
    while (o) {
        int d = o->cmp(x);
        if (d == -1) return 1; //存在
        else o = o->ch[d];
    }
    return 0; //不存在
}

//d=0 代表左旋，d=1 代表右旋
void rotate(node* &o, int d) {
    node* k = o->ch[d^1]; o->ch[d^1] = k->ch[d]; k->ch[d] = o;
    o->maintain(); k->maintain(); o = k; //注意必须先维护o，再维护k
}

//在以o为根的子树中插入键值x，修改o
void insert(node* &o, int x) {
    if (o) {
        // 键值不可重复时
        // if (x == o->v) return;
        int d = x >= o->v;
        insert(o->ch[d], x);
        if (o->ch[d] > o) rotate(o, d^1);
    } else o = new node(x);
    o->maintain();
}

//在以o为根的子树中插入子树t（子树合并）
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

void remove(node* &o, int x) {
    int d = o->cmp(x);
    if (d == -1) {
        if (o->ch[0] && o->ch[1]) {
            int d2 = o->ch[1] < o->ch[0];
            rotate(o, d2); remove(o->ch[d2], x);
        } else {
            node* u = o;
            o = o->ch[1] ? o->ch[1] : o->ch[0];
            delete u;
        }
    } else remove(o->ch[d], x);
    if (o) o->maintain();
}