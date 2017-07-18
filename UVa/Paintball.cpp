/**
 * UVa11853
 * 战场
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <queue>
#include <cmath>
using namespace std;
struct circle{ float x, y, r; };

float p1, p2;

bool way(const circle (&s)[1000], const set<short> (&g)[1000], bool (&visit)[1000], int i){
    queue<short> q; q.push(i); visit[i]=true;
    while(!q.empty()){ i=q.front(); q.pop(); if(s[i].r >= s[i].y) return true;
        if(s[i].r >= s[i].x){ float y=s[i].y-sqrt(s[i].r*s[i].r-s[i].x*s[i].x); if(y<p1) p1=y; }
        if(s[i].r >= 1000-s[i].x){ float y=s[i].y-sqrt(s[i].r*s[i].r-(1000-s[i].x)*(1000-s[i].x)); if(y<p2) p2=y; }
        for(set<short>::const_iterator it=g[i].cbegin(); it!=g[i].cend(); ++it)
            if(!visit[*it]) q.push(*it), visit[*it]=true;
    } return false;
}

bool way(const vector<short>& o, const circle (&s)[1000], const set<short> (&g)[1000], bool (&visit)[1000]){
    for(int l=o.size(), i=0; i<l; ++i) if(!visit[o[i]] && way(s, g, visit, o[i])) return true; return false;
}

int main()
{
    cout << fixed << setprecision(2); short n;
    while(cin>>n){ circle s[1000]; vector<short> o; set<short> g[1000]; bool visit[1000]={0}; p1=1000, p2=1000;
        for(short i=0; i<n; ++i){ cin >> s[i].x >> s[i].y >> s[i].r; if(s[i].r >= 1000-s[i].y) o.push_back(i); }
        for(short i=0; i<n; ++i) for(short j=0; j<n; ++j) if(i!=j && !g[i].count(j) && (s[i].x-s[j].x)*(s[i].x-s[j].x)
            + (s[i].y-s[j].y)*(s[i].y-s[j].y) <= (s[i].r+s[j].r)*(s[i].r+s[j].r)) g[i].insert(j), g[j].insert(i);
        if(o.size()>0 && way(o, s, g, visit)) cout << "IMPOSSIBLE" << endl;
        else cout << "0.00 " << p1 << " 1000.00 " << p2 << endl;
    }
    return 0;
}