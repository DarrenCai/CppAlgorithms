/**
 * UVa12166
 * 修改天平
 */

#include <iostream>
#include <queue>
using namespace std;
struct node{ int val; node *left, *right; node(){val=0; left=right=nullptr;} };

node* build(queue<char>& q){ node *t = new node();
    if(q.front() == '['){ q.pop(); t->left=build(q); q.pop(); t->right=build(q); q.pop();
    } else while(q.front()>='0' && q.front()<='9') t->val = 10*t->val + q.front() - '0', q.pop();
    return t;
}

int dfs(node* t, int id, bool (&visit)[131072]){
    //
}

int main()
{
    short t; cin >> t; cin.get();
    while(t--){ queue<char> q; char c;
        while((c=getchar()) != '\n' && !cin.eof()) q.push(c);
        node* tree = build(q);
        cout << 0 << endl;
    }
    return 0;
}