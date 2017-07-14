/**
 * UVa1599
 * 理想路径
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct ver{int v, c; ver(int v, int c){this->v=v;this->c=c;}};

void bfs(const vector<vector<ver> >&g, vector<int>& d){
    const int n = g.size(); vector<bool> inq(n, false); queue<int> q; q.push(n-1); inq[n-1]=true;
    while(!q.empty()){ int v, u=q.front(); q.pop(); const int l = g[u].size();
        for(int i=0; i<l; ++i) if(!inq[v=g[u][i].v]){ d[v]=d[u]+1; if(!v) return; q.push(v); inq[v]=true; }
    }
}

void bfs(const vector<vector<ver> >&g, const vector<int>& d, vector<int>& c){
    const int n = g.size(); vector<bool> visit(n, false); vector<int> q; q.push_back(0); visit[0]=true;
    while(!q.empty()){ int k=1000000001; vector<int> s(q); q.clear(); const int t=s.size();
        for(int i=0; i<t; ++i){ int v, u=s[i]; if(u==n-1) return; const int l = g[u].size();
            for(int j=0; j<l; ++j) if(!visit[v=g[u][j].v] && d[v]+1==d[u] && g[u][j].c<k) k = g[u][j].c;
        }
        for(int i=0; i<t; ++i){ int v, u=s[i]; const int l = g[u].size();
            for(int j=0; j<l; ++j) if(!visit[v=g[u][j].v] && d[v]+1==d[u] && g[u][j].c==k) q.push_back(v), visit[v]=true;
        }
        c[d[0]-d[s[0]]] = k;
    }
}

int main()
{
    int n, m;
    while(cin >> n >> m){
        vector<vector<ver> > g(n); vector<int> d(n, -1); d[n-1] = 0;
        while(m--){ int a, b, c; cin >> a >> b >> c; if(a == b) continue;
            g[a-1].push_back(ver(b-1,c)); g[b-1].push_back(ver(a-1,c));
        }
        bfs(g, d); vector<int> c(d[0]); bfs(g, d, c);
        cout << d[0] << endl << c[0]; for(int i=1; i<d[0]; ++i) cout << ' ' << c[i]; cout <<endl;
    }
    return 0;
}