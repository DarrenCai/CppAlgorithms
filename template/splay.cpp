struct node {
    node *ch[2];        //左右子树
    int v;              //值
    int s = 0;          //附加域size
    int flip = 0;  //翻转标记
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
            node *p = ch[0]; ch[0] = ch[1]; ch[1] = ch[0];
            ch[0]->flip ^= 1; ch[1]->flip ^= 1;
        }
    }
} *null = new node();

//d=0 代表左旋，d=1 代表右旋
void rotate(node*& o, int d) {
    node* k = o->ch[d^1]; o->ch[d^1] = k->ch[d]; k->ch[d] = o;
    o->maintain(); k->maintain(); o = k; //注意必须先维护o，再维护k
}

void splay(node*& o, int k) {  // 找到序列的左数第k个元素并伸展到根结点
    o->pushdown();
    int d = o->cmp(k);  // 看看第k个元素在整个树中的位置
    if (d == -1) return;               // 已经在根上了
    if (d) k -= o->ch[0]->s + 1;  // 第k个元素在o的右子树中
    node* p = o->ch[d];                // 第k个元素所在的子树
    p->pushdown();
    int d2 = p->cmp(k);  // 第k个元素是在p的左子树?→d2
    if (d2 != -1) {          // 不是子树的根，伸展到p
        splay(p->ch[d2], d2 ? k - p->ch[0]->s - 1 : k);  // 伸展到p的子树根，下面旋转到p
        if (d == d2) rotate(o, d^1);  // 一条直线
        else rotate(o->ch[d], d);  // 不是一条直线
    }
    rotate(o, d^1);  // 从p旋转到o
}

// 合并left和right。假定left的所有元素比right小。注意right可以是null，但left不可以
node* merge(node* left, node* right) {
    splay(left, left->s);
    left->ch[1] = right;
    left->maintain();
    return left;
}

// 把o的前k小结点放在left里，其他的放在right里。1<=k<=o->s。当k=o->s时，right=null
void split(node* o, int k, node*& left, node*& right) {
    splay(o, k);
    left = o;
    right = o->ch[1];
    o->ch[1] = null;
    left->maintain();
}

// build(arr)：把数组arr转化为序列，返回这个序列