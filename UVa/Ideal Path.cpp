/**
 * UVa1599
 * 理想路径
 */

#include <iostream>
#include <map>
#include <algorithm>
// #include <cstdio>
using namespace std;

void bfs(const map<int, map<int, int> > &p, int (&d)[100001], bool (&visit)[100001], const int n, int s){
    visit[s] = true; const map<int, int> &m = p.at(s);
    for(map<int, int>::const_iterator it = m.cbegin(); it != m.cend(); ++it){
        int j = it->first; if(j!=n && (!d[j] || d[s]+1 < d[j])) d[j] = d[s]+1;
    }
    for(map<int, int>::const_iterator it = m.cbegin(); it != m.cend(); ++it)
        if(!visit[it->first]) bfs(p, d, visit, n, it->first);
}

void bfs(const map<int, map<int, int> > &p, const int (&d)[100001], int (&next)[100001], int s){
    int c = 1000000001, f0, f; const map<int, int> &m = p.at(s);
    for(map<int, int>::const_iterator it = m.cbegin(); it != m.cend(); ++it)
        if(d[it->first] + 1 == d[s] && it->second < c) c = it->second, f0 = it->first;
    next[s] = f = f0; if(!d[f]) return; bfs(p, d, next, f0);
    for(map<int, int>::const_iterator it = m.cbegin(); it != m.cend(); ++it)
        if(it->first != f0 && d[it->first] + 1 == d[s] && it->second == c){
            bfs(p, d, next, it->first);
            for(int i = it->first, j = f; d[i]; i = next[i], j = next[j])
                if(p.at(i).at(next[i]) < p.at(j).at(next[j])){ next[s] = f = it->first; break; }
        }
}

int main()
{
    // freopen("in.txt", "r", stdin);
    int n, m;
    while(cin >> n >> m){
        map<int, map<int, int> > p; int d[100001] = {0}; bool visit[100001] = {0}; int next[100001] = {0};
        while(m--){ int a, b, c; cin >> a >> b >> c; if(a == b) continue;
            if (!p.count(a) || !p[a].count(b) || c < p[a][b]) p[a][b] = p[b][a] = c;
        }
        bfs(p, d, visit, n, n); bfs(p, d, next, 1); cout << d[1] << endl << p[1][next[1]];
        for(int i = next[1]; d[i]; i = next[i]) cout << ' ' << p[i][next[i]]; cout << endl;
    }
    return 0;
}