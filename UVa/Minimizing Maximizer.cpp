/**
 * UVa1322
 * 优化最大值电路
 */

#include <iostream>
#include <set>
using namespace std;

struct node {
    int m, n;
    node(int m, int n):m(m), n(n){}
    bool operator< (const node& rhs) const {
        return n < rhs.n;
    }
};
set<node> q;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        int m, n; cin >> n >> m;
        q.clear(); q.insert(node(0, 1));
        for (int i=0; i<m; ++i) {
            int a, b; cin >> a >> b;
            set<node>::iterator it = q.lower_bound(node(0, a));
            if (it != q.end() && it->n < b) {
                node v(it->m+1, b);
                ++ it;
                while (it != q.end() && it->n <= b) it = q.erase(it);
                q.insert(v);
            }
        }
        cout << q.rbegin()->m << endl;
        if (t) cout << endl;
    }
    return 0;
}