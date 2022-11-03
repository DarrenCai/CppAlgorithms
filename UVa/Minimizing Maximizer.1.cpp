/**
 * UVa1322/LA2930
 * 优化最大值电路
 * CERC 2003
 */

#include <iostream>
#include <cstring>
#include <set>
using namespace std;

#define N 50050
int d[N];

int solve() {
    set<int> q; memset(d, 1, sizeof(d)); d[1] = 0; q.insert(1);
    int m, n; cin >> n >> m;
    while (m--) {
        int i, j; cin >> i >> j;
        set<int>::iterator it = q.lower_bound(i);
        if (it != q.end() && *it < j) {
            int v = d[*it++] + 1;
            while (it != q.end() && *it <= j) it = q.erase(it);
            if (it == q.end() || d[*it] > v) q.insert(j), d[j] = v;
        }
    }
    return d[n];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    short t; cin >> t;
    while (t--) {
        cout << solve() << endl;
        if (t) cout << endl;
    }
    return 0;
}