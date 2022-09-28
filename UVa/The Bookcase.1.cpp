/**
 * UVa12099/LA3637
 * 书架
 * NWERC 2006
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define min(a, b) (a<b ? a : b)
#define max(a, b) (a>b ? a : b)
#define N 75
struct book {
    short h, w;
    bool operator< (const book& rhs) const {
        return h > rhs.h;
    }
} b[N];
short d[1070][735];

int solve() {
    int s = 0, x = 0, n; cin >> n;
    for (int i=1; i<=n; ++i) cin >> b[i].h >> b[i].w, s += b[i].w, x = max(x, b[i].w);
    memset(d, 4, sizeof(d));
    sort(b+1, b+n+1);
    int m = (s+x) / 2, t = s/3 + x;
    for (int i=1, w=0; i<=n; w += b[i++].w)
        for (int k=min(w, t); k>=0; --k) for (int j=min(m, w-k), jj=max(k-x, 0), v; j>=jj; --j) {
            if (j==0 && k==0 && w==0) {
                d[j][k] = min(d[j][k], b[i].h);
                if ((v = j+b[i].w) <= m) d[v][k] = min(d[v][k], 2*b[i].h);
                if ((v = k+b[i].w) <= t) d[j][v] = min(d[j][v], 3*b[i].h);
            } else if (j==0 && k==0) {
                if ((v = j+b[i].w) <= m) d[v][k] = min(d[v][k], d[j][k] + b[i].h);
                if ((v = k+b[i].w) <= t) d[j][v] = min(d[j][v], d[j][k] + 2*b[i].h);
            } else if (k==0) {
                if ((v = j+b[i].w) <= m) d[v][k] = min(d[v][k], d[j][k]);
                if ((v = k+b[i].w) <= t) d[j][v] = min(d[j][v], d[j][k] + b[i].h);
            } else {
                if ((v = j+b[i].w) <= m) d[v][k] = min(d[v][k], d[j][k]);
                if ((v = k+b[i].w) <= t) d[j][v] = min(d[j][v], d[j][k]);
            }
        }
    int ans = 3*s*b[1].h;
    for (int k=t; k>0; --k) for (int j=min(m, s-k-1), jj=max(k-x, 1), w; j>=jj; --j)
        if ((w = s-j-k) > 0 && w+x >= j) ans = min(ans, max(w, max(j, k))*d[j][k]);
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}