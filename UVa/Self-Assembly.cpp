/**
 * UVa1572
 * 自组合
 */

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;
#include <cstdio>

bool compatible(int a, int b){
    for(int i=0; i<4; ++i, a>>=6){
        int e1 = a & 63; if(!e1) continue;
        for(int j=0; j<4; ++j, b>>=6){
            int e2 = b & 63; if(!e2) continue;
            if((e1&32) != (e2&32) && (e1&31) == (e2&31)) return true;
        }
    }
    return false;
}

bool search(const vector<unordered_set<int> >& a, vector<bool>& visit, int i, unordered_set<int>& path){
    if(path.count(i)) return true;
    visit[i] = true; path.insert(i);
    for(auto e: a[i]){
        unordered_set<int> p(path);
        if(search(a, visit, e, p)) return true;
    }
    return false;
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("ou.txt", "w", stdout);
    int n;
    while(cin >> n){
        vector<int> m(n); vector<unordered_set<int> > a(n); vector<bool> visit(n, false);
        for(int i=0; i<n; ++i){
            int v = 0;
            for(int j=0; j<4; ++j){
                char c0, c1; cin >> c0 >> c1;
                v = (v<<6) + (c0=='0' ? 0 : c0-'A'+(c1=='+' ? 32:0));
            }
            m[i] = v;
        }
        for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) if(!a[i].count(j) && compatible(m[i], m[j])) a[i].insert(j), a[j].insert(i);
        bool bounded = true;
        for(int i=0; i<n; ++i){
            unordered_set<int> path;
            if(!visit[i] && search(a, visit, i, path)){ bounded = false; break; }
        }
        cout << (bounded ? "bounded" : "unbounded") << endl;
    }
    return 0;
}