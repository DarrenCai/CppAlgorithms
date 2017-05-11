/**
 * UVa839
 * 天平
 */

#include <iostream>
#include <cstdio>

using namespace std;

struct node {
    int w;
    node *left, *right;
    node():left(nullptr),right(nullptr){}
};

node* build() {
    int Wl,Wr,Dl,Dr;
    cin >> Wl >> Dl >> Wr >> Dr;
    node *t = new node();
    if(Wl && Wr) {
        if(Wl*Dl!=Wr*Dr)    {delete t; return nullptr;}
        t->w = Wl + Wr; return t;
    }
    if(!Wl)     t->left = build();
    if(!Wr)     t->right = build();
    if(!t->left || !t->right) {
        if(t->left)     delete t->left;
        if(t->right)    delete t->right;
        delete t; return nullptr;
    }
    if(t->left->w*Dl != t->right->w*Dr) {
        delete t->left; delete t->right;
        delete t; return nullptr;
    }
    t->w = t->left->w + t->right->w;
    delete t->left; delete t->right;
    return t;
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while(t--) {
        node *root = build();
        cout << (root ? "YES" : "NO") << endl;
        if(root)    delete root;
        if(t)   cout << endl;
    }
    return 0;
}