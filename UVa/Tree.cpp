/**
 * UVa548
 * 树
 */

#include <iostream>
#include <string>
#include <deque>
#include <stack>

struct node {
    int val;
    node *left, *right;
};

int main()
{
    using namespace std;
    string line1, line2;
    while(getline(cin, line1) && getline(cin, line2)) {
        deque<int> inOrder; stack<int> postOrder;
        line1 += ' '; line2 += ' ';
        int len=line1.length();
        for(int v=0,i=0; i<len; ++i) {
            if(line1[i] == ' ') { inOrder.push_back(v); v=0; }
            else v=10*v + line1[i]-'0';
        }
        for(int v=0,i=0; i<len; ++i) {
            if(line2[i] == ' ') { postOrder.push(v); v=0; }
            else v=10*v + line2[i]-'0';
        }
    }
    return 0;
}