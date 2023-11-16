/**
 * UVa12130/LA3977
 * NWERC 2007
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 252004
int h[N], s[N], f[N], q[N], t, r, c, d;

bool cmp(int i, int j) {
    return h[i] > h[j];
}

int bfs(int u, int g) {
    int head = 0, tail = 1, gd = g-d, cc = 1, gx = g; f[q[0] = u] = g;
    while (head < tail) {
        u = q[head++];
        int x = u/c, y = u%c, v;
        if (x > 0 && h[v = (x-1)*c + y] > gd)
            if (f[v] < 0) {
                if (h[v] == g) ++cc;
                q[tail++] = v; f[v] = g;
            } else gx = max(f[v], gx);
        if (x+1 < r && h[v = (x+1)*c + y] > gd)
            if (f[v] < 0) {
                if (h[v] == g) ++cc;
                q[tail++] = v; f[v] = g;
            } else gx = max(f[v], gx);
        if (y > 0 && h[v = x*c + y-1] > gd)
            if (f[v] < 0) {
                if (h[v] == g) ++cc;
                q[tail++] = v; f[v] = g;
            } else gx = max(f[v], gx);
        if (y+1 < c && h[v = x*c + y+1] > gd)
            if (f[v] < 0) {
                if (h[v] == g) ++cc;
                q[tail++] = v; f[v] = g;
            } else gx = max(f[v], gx);
    }
    if (gx > g) while (tail--) f[q[tail]] = gx;
    return gx > g ? 0 : cc;
}

void solve() {
    cin >> r >> c >> d;
    for (int i=t=0; i<r; ++i) for (int j=0; j<c; ++j) f[s[t] = t] = -1, cin >> h[t++];
    sort(s, s+t, cmp);
    int ans = 0;
    for (int i=0; i<t; ++i) if (f[s[i]] < 0) ans += bfs(s[i], h[s[i]]);
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}