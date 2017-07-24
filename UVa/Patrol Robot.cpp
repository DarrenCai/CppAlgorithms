/**
 * UVa1600
 * 巡逻机器人
 */

#include <iostream>
#include <queue>
#include <set>
using namespace std;
char s[20][20]; short m, n, k, mi;
const char d[4][2]={{-1,0},{0,-1},{1,0},{0,1}};

short dfs(){ queue<pair<set<pair<char,char> >,char> > paths; queue<pair<char,char> > q; q.push(make_pair(0,0));
    pair<set<pair<char,char> >,char> p1, p; p.first.insert(q.front()); p.second=0; paths.push(p);
    while(!q.empty()){ p = paths.front(); paths.pop(); char r0=q.front().first, c0=q.front().second; q.pop(); pair<char,char> t;
        for(char i=0; i<4; ++i){char r=r0+d[i][0], c=c0+d[i][1]; if(r<0 || r>=m || c<0 || c>=n || p.first.count(t=make_pair(r,c))) continue;
            if(p.second+s[r][c]<=k){if(r==m-1 && c==n-1) return p.first.size(); q.push(t); p1=p;
                p1.first.insert(t); if(s[r][c]) ++p1.second; else p1.second=0; paths.push(p1);} }
    } return -1;
}

int main()
{
    short t; cin >> t;
    while(t--){ mi=200; cin >> m >> n >> k;
        for(char i=0; i<m; ++i) for(int j=0; j<n; ++j) cin >> s[i][j], s[i][j] -= '0';
        cout << dfs() << endl;
    }
    return 0;
}