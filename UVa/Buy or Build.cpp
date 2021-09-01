/**
 * UVa1151
 * 买还是建
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 1005
#define Q 10
struct node {
    short u, v; int w;
    bool operator< (const node& rhs) const {
        return w < rhs.w;
    }
} e[N*(N-1)/2];

int sw[Q], c[N][2]; short s[Q][N], cc[Q], p[N];

short find(short x) {
    return p[x]==x ? x : p[x] = find(p[x]);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        int n, q, m = 0;
        cin >> n >> q;
        for (short i=0; i<q; ++i) {
            cin >> cc[i] >> sw[i];
            for (short j=0; j<cc[i]; ++j) cin >> s[i][j];
        }
        for (short i=1; i<=n; ++i) cin >> c[i][0] >> c[i][1];
        for (short i=1; i<n; ++i) for (short j=i+1; j<=n; ++j) {
            e[m].u = i; e[m].v = j;
            e[m++].w = (c[i][0]-c[j][0])*(c[i][0]-c[j][0]) + (c[i][1]-c[j][1])*(c[i][1]-c[j][1]);
        }
        sort(e, e+m);
        long long ans = 1e10;
        for (short i=(1<<q)-1; i>=0; --i) {
            short cnt = n; long long v = 0;
            for (short j=1; j<=n; ++j) p[j] = j;
            for (short j=0; j<q; ++j) if (i&(1<<j)) {
                v += sw[j];
                short x = find(s[j][0]);
                for (short k=1; k<cc[j]; ++k) {
                    short y = find(s[j][k]);
                    if (x != y) {
                        p[y] = x;
                        --cnt;
                    }
                }
            }
            if (cnt == 1) {
                ans = min(ans, v);
                continue;
            }
            for (int j=0; j<m; ++j) {
                short x = find(e[j].u), y = find(e[j].v);
                if (x != y) {
                    p[x] = y;
                    v += e[j].w;
                }
            }
            ans = min(ans, v);
        }
        cout << ans << endl;
        if (t) cout << endl;
    }
}