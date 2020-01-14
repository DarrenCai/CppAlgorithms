/**
 * UVa1623
 * 神龙喝水
 */

#include <iostream>
#include <cstring>
#include <set>
using namespace std;

#define N 1000010
int ans[N], p[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        set<int> s; memset(p, -1, sizeof(p));
        int h=0, f=1, n, m; cin >> n >> m;
        for (int i=0, v; i<m; ++i) {
            cin >> v;
            if (f) {
                if (v) {
                    set<int>::iterator it = s.upper_bound(p[v]);
                    if (it == s.end()) f = 0;
                    else {
                        ans[*it] = v;
                        p[v] = h-1;
                        s.erase(it);
                    }
                } else {
                    s.insert(h);
                    ans[h++] = 0;
                }
            }
        }
        cout << (f ? "YES" : "NO") << endl;
        if (f) for (int i=0; i<h; ++i) cout << ans[i] << (i==h-1 ? '\n' : ' ');
    }
    return 0;
}