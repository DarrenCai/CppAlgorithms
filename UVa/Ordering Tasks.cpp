/**
 * UVa10305
 * 给任务排序
 */

#include <iostream>
#include <deque>
#include <map>
#include <set>
#include <cstdio>

using namespace std;

void insert(int v, map<int, set<int> >& prec, deque<int>& q, set<int>& visit) {
    if(!visit.count(v)) {
        if(prec.count(v)) for(set<int>::iterator it=prec[v].begin(); it!=prec[v].end(); ++it) insert(*it, prec, q, visit);
        q.push_front(v); visit.insert(v);
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("ou.txt", "w", stdout);
    int m, n;
    while(cin>>m>>n && m && n) {
        map<int, set<int> > prec; deque<int> q; set<int> visit;
        while(n--) { int i, j; cin >> i >> j; prec[i].insert(j); }
        for(int i=1; i<=m; ++i) insert(i, prec, q, visit);
        cout << q[0]; for(int i=1; i<m; ++i) cout << ' ' << q[i]; cout << endl;
    }
    return 0;
}