/**
 * UVa1600
 * 巡逻机器人
 */

#include <iostream>
#include <set>
using namespace std;
char s[20][20]; short m, n, k, mi, ki;

void dfs(char r, char c, short ki, set<pair<char,char> > visit){
    visit.insert(pair<char,char>(r,c)); if(s[r][c]=='0') ki=0; else if(++ki>k) return;
    if((r==m-1 && c==n-2) || (r==m-2 && c==n-1)){short t=visit.size(); if(t<mi) mi=t; return;}
    if(c+1<n && !visit.count(pair<char,char>(r,c+1))) dfs(r,c+1,ki,visit);
    if(r+1<m && !visit.count(pair<char,char>(r+1,c))) dfs(r+1,c,ki,visit);
    if(c-1>=0 && !visit.count(pair<char,char>(r,c-1))) dfs(r,c-1,ki,visit);
    if(r-1>=0 && !visit.count(pair<char,char>(r-1,c))) dfs(r-1,c,ki,visit);
}

int main()
{
    short t; cin >> t;
    while(t--){ mi=200; ki=0; cin >> m >> n >> k;
        for(char i=0; i<m; ++i) for(int j=0; j<n; ++j) cin >> s[i][j];
        if(m==1 && n==1) mi=0; else dfs(0,0,0,set<pair<char,char> >());
        cout << (mi==200 ? -1 : mi) << endl;
    }
    return 0;
}