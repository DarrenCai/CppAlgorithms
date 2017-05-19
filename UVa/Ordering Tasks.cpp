/**
 * UVa10305
 * 给任务排序
 * 用dfs解决拓扑排序，这个题要注意边界：只有一个数时？
 */

#include <iostream>
#include <deque>
#include <map>
#include <set>

using namespace std;

void insert(int v, map<int, set<int> >& prec, deque<int>& q, set<int>& visit) {
    if(!visit.count(v)) {
        if(prec.count(v)) for(set<int>::iterator it=prec[v].begin(); it!=prec[v].end(); ++it) insert(*it, prec, q, visit);
        q.push_front(v); visit.insert(v);
    }
}

int main()
{
    int m, n;
    while(cin>>m>>n && m) {     // 原来写的是 while(cin>>m>>n && m && n) { 就忽略了可能m=1,n=0
        map<int, set<int> > prec; deque<int> q; set<int> visit;
        while(n--) { int i, j; cin >> i >> j; prec[i].insert(j); }
        for(int i=1; i<=m; ++i) insert(i, prec, q, visit);
        cout << q[0]; for(int i=1; i<m; ++i) cout << ' ' << q[i]; cout << endl;
    }
    return 0;
}