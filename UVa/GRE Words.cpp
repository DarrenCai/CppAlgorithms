/**
 * UVa1502/LA5766
 * Chengdu 2011
 * 坑点：这题数据好像是出了点锅(SPOJ上这么说的)，所以用除了scanf之外的读入方式可能会造成莫名其妙的TLE或者WA。
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

#define N 20020
#define L 300050
#define C 26
struct {int ch[C], v, f, last;} s[L]; int q[L], g[N][N], c[N], d[N], w[N], n, t, ans; string p[N]; char buf[L];

void update(int x, int i) {
    if (x) {
        int v = s[x].v;
        if (v < i) d[i] = max(d[i], d[c[v] ? g[v][lower_bound(g[v], g[v]+c[v], i) - g[v] - 1] : v]);
        update(s[x].last, i);
    }
}

int solve() {
    scanf("%d", &n);
    memset(s, ans = t = 0, sizeof(s[0]));
    for (int i=1, x; i<=n; ++i) {
        scanf("%s%d", buf, w+i); p[i].assign(buf);
        w[i] = max(w[i], 0); c[i] = d[i] = 0;
        for (int j=x=0; p[i][j]; ++j) {
            int &r = s[x].ch[p[i][j]-'a'];
            if (!r) memset(s + (r = ++t), 0, sizeof(s[0]));
            x = r;
        }
        s[x].v ? g[s[x].v][c[s[x].v]++] = i : g[i][c[i]++] = s[x].v = i;
    }
    int head = 0, tail = 0;
    for (int i=0, u; i<C; ++i) if (u = s[0].ch[i]) q[tail++] = u;
    while (head < tail) {
        int x = q[head++];
        for (int i=0; i<C; ++i) {
            int &u = s[x].ch[i];
            if (!u) {
                u = s[s[x].f].ch[i];
                continue;
            }
            q[tail++] = u;
            int &f = s[u].f = s[s[x].f].ch[i];
            s[u].last = s[f].v ? f : s[f].last;
        }
    }
    for (int i=1; i<=n; ++i) {
        for (int j=0, x=0; p[i][j]; ++j) {
            x = s[x].ch[p[i][j]-'a'];
            if (s[x].v) update(x, i);
            else if (s[x].last) update(s[x].last, i);
        }
        ans = max(ans, d[i] += w[i]);
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; scanf("%d", &t);
    for (int kase=1; kase<=t; ++kase) printf("Case #%d: %d\n", kase, solve());
    return 0;
}