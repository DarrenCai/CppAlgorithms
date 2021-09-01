/**
 * UVa1395
 * 苗条的生成树
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 105
#define INF 10010

struct node {
    short u, v, w;
    bool operator< (const node& rhs) const {
        return w < rhs.w;
    }
} s[N*(N-1)/2];
short p[N];

short find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n, m;
    while (cin>>n>>m && (n || m)) {
        short ans = INF;
        if (m > 0) {
            for (short i=0; i<m; ++i) cin >> s[i].u >> s[i].v >> s[i].w;
            sort(s, s+m);
            for (short l=0; l<m; ++l) {
                short cnt = n, r;
                for (short i=1; i<=n; ++i) p[i] = i;
                for (r=l; r<m; ++r) {
                    int x = find(s[r].u), y = find(s[r].v);
                    if (x != y) p[x] = y, --cnt;
                    if (cnt == 1) break;
                }
                if (cnt > 1) break;
                ans = min(ans, short(s[r].w-s[l].w));
            }
        }
        cout << (ans == INF ? -1 : ans) << endl;
    }
}