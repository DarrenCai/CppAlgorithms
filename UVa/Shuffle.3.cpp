/**
 * UVa12174/LA4294
 * Shuffle的播放记录
 * NWERC 2008
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 100005
int p[N], e[N], r[N], f[N], s, n;

int solve() {
    cin >> s >> n;
    memset(p, -1, sizeof(p)); memset(e, 0, sizeof(e)); memset(r, -1, sizeof(r)); memset(f, 0, sizeof(f));
    for (int i=0; i<n; ++i) {
        int x; cin >> x;
        if (p[x] >= 0) e[r[i] = p[x]] = i;
        p[x] = i;
    }
    int ans = 1;
    for (int i=1; i<n; ++i) {
        int k = (i-1)/s + 1;
        if(e[i] && e[i] < k*s+1) ++f[k], ans = 0;
    }
    for (int i=1, x=min(s, n); i<x; ++i) {
        if(r[i]>=0) {
            ++f[0]; break;
        }
        int ok = 1;
        for (int j=i, k=1; j<n; j+=s, ++k) {
            if (j+s<n && r[j+s]>j) ++f[k];
            if (e[j] && e[j] < k*s+i) --f[k];
            if (f[k]) ok = 0;
        }
        ans += ok;
    }
    return n<s && f[0]==0 ? s : ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}