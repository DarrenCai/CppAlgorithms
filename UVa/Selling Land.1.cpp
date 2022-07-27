/**
 * UVa12265/LA4950
 * 贩卖土地
 * NWERC 2010
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1010
int cnt[N<<2], h[N], m, n;
struct {int h, i;} q[N];

void solve() {
    cin >> n >> m;
    memset(cnt, 0, sizeof(cnt)); memset(h, 0, sizeof(h));
    for (int i=0; i<n; ++i) for (int j=0, t=-1; j<m; ++j) {
        char c; cin >> c;
        c == '#' ? (h[j] = 0, t = -1) : ++h[j];
        q[++t].h = h[j]; q[t].i = j-1;
        while (t > 0 && q[t].h - q[t].i < q[t-1].h - q[t-1].i) {
            if (q[t].h < q[t-1].h) q[t-1].h = q[t].h;
            --t;
        }
        ++cnt[(j+q[t].h-q[t].i)<<1];
    }
    for (int i=4, t=(m+n)<<1; i<=t; ++i) if (cnt[i]) cout << cnt[i] << " x " << i << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}