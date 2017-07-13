/**
 * UVa1599
 * 理想路径
 */

#include <iostream>
#include <vector>
// #include <cstdio>
using namespace std;

void bfs(const vector<int> (&g)[100001], int (&d)[100001], bool (&visit)[100001], const int n, int s){
    visit[s] = true; const vector<int>& m = g[s]; const int l = m.size();
    for(int i=0; i<l; ++i) if(m[i]!=n && (!d[m[i]] || d[s]+1 < d[m[i]])) d[m[i]] = d[s]+1;
    for(int i=0; i<l; ++i) if(!visit[m[i]]) bfs(g, d, visit, n, m[i]);
}

void bfs(const vector<int> (&g)[100001], const vector<int> (&k)[100001], const int (&d)[100001], int (&next)[100001], int s){
    int c = 1000000001, f0, f; const vector<int>& m = g[s]; const int l = m.size();
    for(int i=0; i<l; ++i) if(d[m[i]]+1 == d[s] && k[s][i] < c) c = k[s][i], f0 = i;
    next[s] = f = f0; if(!d[m[f0]]) return; bfs(g, k, d, next, m[f0]);
    for(int i=0; i<l; ++i)
        if(i != f0 && d[m[i]]+1 == d[s] && k[s][i] == c){ bfs(g, k, d, next, m[i]);
            for(int j=m[i], t=m[f]; d[j]; j=g[j][next[j]], t=g[t][next[t]]) if(k[j][next[j]] < k[t][next[t]]){ next[s] = f = i; break; }
        }
}

int main()
{
    // freopen("in.txt", "r", stdin);
    int n, m;
    while(cin >> n >> m){
        vector<int> g[100001], k[100001]; int d[100001]={0}, next[100001]={0}; bool visit[100001] = {0};
        while(m--){ int a, b, c; cin >> a >> b >> c; if(a == b) continue;
            g[a].push_back(b); k[a].push_back(c); g[b].push_back(a); k[b].push_back(c);
        }
        bfs(g, d, visit, n, n); bfs(g, k, d, next, 1); cout << d[1] << endl << k[1][next[1]];
        for(int i = g[1][next[1]]; d[i]; i = g[i][next[i]]) cout << ' ' << k[i][next[i]]; cout << endl;
    }
    return 0;
}