/**
 * UVa439
 * 骑士的移动
 */

#include <iostream>
#include <string>
#include <queue>
using namespace std;
#define min(a,b) a<b ? a:b
#define max(a,b) a>b ? a:b
char s[64][64] = {0};

void calc(char c){ queue<char> q; bool visit[64]={0}; q.push(c); visit[c]=true;
    while(!q.empty()){ char a=q.front(), xa=a&7, ya=a>>3; q.pop();
        if(xa-2>=0 && ya-1>=0){ char b=(ya-1<<3)+xa-2; if(!visit[b]){
            s[min(c,b)][max(c,b)]=s[min(c,a)][max(c,a)]+1; q.push(b); visit[b]=true;} }
        if(xa+2<=7 && ya-1>=0){char b=(ya-1<<3)+xa+2; if(!visit[b]){
            s[min(c,b)][max(c,b)]=s[min(c,a)][max(c,a)]+1; q.push(b); visit[b]=true;} }
        if(xa-2>=0 && ya+1<=7){char b=(ya+1<<3)+xa-2; if(!visit[b]){
            s[min(c,b)][max(c,b)]=s[min(c,a)][max(c,a)]+1; q.push(b); visit[b]=true;} }
        if(xa+2<=7 && ya+1<=7){char b=(ya+1<<3)+xa+2; if(!visit[b]){
            s[min(c,b)][max(c,b)]=s[min(c,a)][max(c,a)]+1; q.push(b); visit[b]=true;} }
        if(xa-1>=0 && ya-2>=0){char b=(ya-2<<3)+xa-1; if(!visit[b]){
            s[min(c,b)][max(c,b)]=s[min(c,a)][max(c,a)]+1; q.push(b); visit[b]=true;} }
        if(xa-1>=0 && ya+2<=7){char b=(ya+2<<3)+xa-1; if(!visit[b]){
            s[min(c,b)][max(c,b)]=s[min(c,a)][max(c,a)]+1; q.push(b); visit[b]=true;} }
        if(xa+1<=7 && ya-2>=0){char b=(ya-2<<3)+xa+1; if(!visit[b]){
            s[min(c,b)][max(c,b)]=s[min(c,a)][max(c,a)]+1; q.push(b); visit[b]=true;} }
        if(xa+1<=7 && ya+2<=7){char b=(ya+2<<3)+xa+1; if(!visit[b]){
            s[min(c,b)][max(c,b)]=s[min(c,a)][max(c,a)]+1; q.push(b); visit[b]=true;} }
    }
}

int main()
{
    string s1, s2;
    while(cin >> s1 >> s2){ char a=(s1[0]-'a'<<3)+s1[1]-'1', b=(s2[0]-'a'<<3)+s2[1]-'1';
        if(a>b){ char t=a; a=b; b=t; } if(a!=b && !s[a][b]) calc(a);
        cout << "To get from " << s1 <<" to " << s2 << " takes " << (short)s[a][b] << " knight moves." << endl;
    }
    return 0;
}