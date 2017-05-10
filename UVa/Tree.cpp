/**
 * UVa548
 * 树
 */

#include <iostream>
#include <deque>
#include <cstdio>

using namespace std;

struct node {
    int val;
    node *left, *right;
    node(int val=0):left(nullptr),right(nullptr){this->val = val;}
};

node * buildTree(deque<int>& inOrder, deque<int>& postOrder) {
    if(postOrder.empty())   return nullptr;
    const int val = postOrder.back();
    node* t = new node(val);
    postOrder.pop_back();
    deque<int> right;
    while(inOrder.back() != val) {
        right.push_front(inOrder.back());
        inOrder.pop_back();
    }
    inOrder.pop_back();
    if(!right.empty())    t->right = buildTree(right, postOrder);
    if(!inOrder.empty())  t->left = buildTree(inOrder, postOrder);
    return t;
}

void traverse(const node* t, int& min, int& leaf, int sum=0) {
    sum += t->val;
    if(sum > min) return;
    if(t->left && t->right) {
        traverse(t->left, min, leaf, sum);
        traverse(t->right, min, leaf, sum);
    }
    else if(t->left)    traverse(t->left, min, leaf, sum);
    else if(t->right)   traverse(t->right, min, leaf, sum);
    else if(sum<min || (sum==min && t->val<leaf)) {
        min = sum; leaf = t->val;
    }
}

void destoryTree(node *t) {
    if(t && t->left)     destoryTree(t->left);
    if(t && t->right)    destoryTree(t->right);
    if(t)   delete t;
}

int main()
{
    char c; int v, line=0; deque<int> q[2];
    freopen("in.txt", "r", stdin);
    freopen("ou.txt", "w", stdout);
    while(!cin.eof() && (c=cin.get())) {
        if(c==' ' || c=='\n') {
            q[line].push_back(v); v=0;
            if(c == '\n') {
                line ^= 1;
                if(line == 0) {
                    node *t = buildTree(q[0], q[1]);
                    int min = 100000000, leaf=10000;
                    traverse(t, min, leaf);
                    cout << leaf << endl;
                    destoryTree(t);     // q[0].clear(); q[1].clear();
                }
            } 
        }
        else v=10*v + c-'0';
    }
    return 0;
}