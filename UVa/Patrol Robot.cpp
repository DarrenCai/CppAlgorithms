/**
 * UVa1600
 * 巡逻机器人
 */

#include <iostream>
#include <queue>
using namespace std;
char s[20][20]; short m, n, k, mi;
const char d[4][2] = {{-1,0},{0,-1},{1,0},{0,1}};
struct p{char r, c; short t, s; p(char r, char c, short t, short s):r(r),c(c),t(t),s(s){}};

short dfs(){ bool visit[20][20]={0}; short f[20][20]={0}; queue<p > q; q.push(p(0,0,0,0)); visit[0][0] = true;
    while(!q.empty()){ char r0=q.front().r, c0=q.front().c; short t0=q.front().t, st=q.front().s+1; q.pop();
        for(char i=0; i<4; ++i){ char r=r0+d[i][0], c=c0+d[i][1]; if(r<0 || r>=m || c<0 || c>=n) continue;
            short t = s[r][c]=='1' ? t0+1 : 0; if(visit[r][c] && t>=f[r][c]) continue; visit[r][c]=true;
            if(!f[r][c] || t<f[r][c]) f[r][c] = t; if(t <= k){if(r==m-1 && c==n-1) return st; q.push(p(r,c,t,st));} }
    } return -1;
}

int main()
{
    short t; cin >> t;
    while(t--){ mi=200; cin >> m >> n >> k;
        for(char i=0; i<m; ++i) for(int j=0; j<n; ++j) cin >> s[i][j];
        cout << dfs() << endl;
    }
    return 0;
}