/**
 * UVa536
 * 二叉树重建
 */

#include <iostream>
#include <string>
#include <queue>
using namespace std;

void tree(char (&post)[27], char& p, queue<char>& pre, queue<char>& ino){
    post[p] = pre.front(); pre.pop(); queue<char> preL, inoL;
    while(ino.front()!=post[p]){ preL.push(pre.front()); pre.pop(); inoL.push(ino.front()); ino.pop(); }
    ino.pop(); if(!pre.empty()) tree(post, --p, pre, ino); if(!preL.empty()) tree(post, --p, preL, inoL);
}

int main()
{
    string s1, s2;
    while(cin >> s1 >> s2){ char post[27]={0}, p=-1; queue<char> pre, ino;
        while(s1[++p]){ pre.push(s1[p]); ino.push(s2[p]); } tree(post, --p, pre, ino); cout << post << endl;
    }
    return 0;
}