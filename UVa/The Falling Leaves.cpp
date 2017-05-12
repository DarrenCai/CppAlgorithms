/**
 * UVa699
 * 下落的树叶
 */

#include <iostream>
#include <map>

using namespace std;

bool build(map<int, int>& ret, int p=0) {
    int v; cin >> v;
    if(v == -1)     return false;
    ret.count(p) ? ret[p] += v : ret[p] = v;
    build(ret, p-1); build(ret, p+1);
    return true;
}

int main()
{
    map<int, int> ret; int k=0;
    while(build(ret)) {
        cout << "Case " << ++k << ":" << endl;
        map<int, int>::const_iterator it = ret.begin();
        cout << it->second;
        while(++it != ret.end()) cout << ' ' << it->second;
        cout << endl << endl;
        ret.clear();
    }
    return 0;
}