/**
 * UVa1381/LA3693
 * Asia Regional Shanghai 2006
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct node {
    int w, s;
    bool operator< (const node& rhs) const {
        return w < rhs.w || (w==rhs.w && s<rhs.s);
    }
} r[65536], q[65536];

int a[16], b[65536], c[65536], t, kase = 0; bool vis[16] = {false};

int bits(int x) {
    int cnt = 0;
    while (x > 0) x = x&(x-1), ++cnt;
    return cnt;
}

void solve() {
    for (int i=1; i<16; ++i) cin >> a[i];
    memset(c, 0, sizeof(c));
    for (int x1=t=0; x1<16; ++x1) if (!vis[x1]) {
        vis[x1] = true;
        for (int x2=0; x2<16; ++x2) if (!vis[x2]) {
            vis[x2] = true;
            for (int x3=0; x3<16; ++x3) if (!vis[x3]) {
                vis[x3] = true;
                for (int x4=0; x4<16; ++x4) if (!vis[x4]) {
                    vis[x4] = true;
                    r[t].w = a[x1]*4 + a[x2]*3 + a[x3]*2 + a[x4];
                    r[t++].s = 1<<x1 | 1<<x2 | 1<<x3 | 1<<x4;
                    vis[x4] = false;
                }
                vis[x3] = false;
            }
            vis[x2] = false;
        }
        vis[x1] = false;
    }
    sort(r, r+t); r[t].w = 0; q[0].w = 1; q[0].s = r[0].s;
    for(int i=1, w=r[0].w, s=r[0].s, x=0; i<=t; w = r[i].w, s = r[i].s, ++i) {
        if (r[i].w != w) {
            for (int j=0; j<x; ++j) for (int k=j+1; k<=x; ++k)
                if (!(q[j].s & q[k].s)) c[q[j].s | q[k].s] += q[j].w * q[k].w;
            q[0].w = 1; q[x=0].s = r[i].s;
        } else r[i].s == s ? ++q[x].w : (q[++x].w=1, q[x].s=r[i].s);
    }
    int ans = 0;
    for (int i=0; b[i]<32768; ++i) ans += c[b[i]] * c[65535 ^ b[i]];
    cout << "Case " << ++kase << ": " << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=0, t=0; i<65536; ++i) if (bits(i) == 8) b[t++] = i;
    while (cin>>a[0] && a[0]) solve();
    return 0;
}