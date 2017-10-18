/**
 * UVa10410
 * 树重建
 */

#include <iostream>
#include <deque>
#include <vector>
using namespace std;

void build(deque<short> &bfs, short* dfs, short n, short (&lv)[1001]) {
    short f = bfs.front(), fn; bfs.pop_front(); fn = bfs.front();
    if (lv[fn] < lv[f]) lv[fn] = lv[f];
    if (dfs[1] != fn) {
        short t=1; deque<short> bfs1;
        while(dfs[t] != fn && t<n) lv[dfs[t++]] = lv[f]+1;
        while(bfs.front() != dfs[1]) {
            bfs1.push_back(bfs.front()); lv[bfs.front()] = lv[f]; bfs.pop_front();
        }
        if (t > 2) build(bfs, dfs+1, t-1, lv);
        else bfs.pop_front();
        if (!bfs.empty()) {
            fn = bfs.front();
            if (lv[fn] < lv[dfs[1]]) lv[fn] = lv[dfs[1]];
        }
        while(!bfs1.empty()) {
            bfs.push_front(bfs1.back()); bfs1.pop_back();
        }
        if (n>t+1) build(bfs, dfs+t, n-t, lv);
    } else {
        if (dfs[1] < f) lv[dfs[1]] = lv[f] + 1;
        if (n>2) build(bfs, dfs+1, n-1, lv);
        else bfs.pop_front();
    }
}

void build(short (&dfs)[1000], short (&lv)[1001], short (&parent)[1001], vector<vector<short> > &child) {
    short n = child.size();
    for (short i=0; i<n-1; ++i) {
        short pa = dfs[i];
        for(short l=lv[dfs[i+1]]; l<=lv[dfs[i]]; ++l) pa=parent[pa];
        parent[dfs[i+1]] = pa; child[pa-1].push_back(dfs[i+1]);
    }
}
 
int main()
{
    short n, dfs[1000], lv[1001], parent[1001];
    while (cin>>n) {
        deque<short> bfs; vector<vector<short> > child(n);
        for (short i=0; i<n; ++i) {
            short v; cin >> v; bfs.push_back(v);
        }
        for (short i=0; i<n; ++i) {
            cin >> dfs[i]; lv[dfs[i]] = 1;
        }
        if (n > 1) {
            lv[dfs[0]] = 0; bfs.pop_front();
            if(n>2) build(bfs, dfs+1, n-1, lv);
            build(dfs, lv, parent, child);
        }
        for (short i=0; i<n; ++i) {
            cout << i+1 << ':';
            short size = child[i].size();
            for (short j=0; j<size; ++j) cout << ' ' << child[i][j];
            cout << endl;
        }
    }
    return 0;
}