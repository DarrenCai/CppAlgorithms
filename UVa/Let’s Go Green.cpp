/**
 * UVa1668
 * 绿色行动
 */

#include <iostream>
using namespace std;

#define N 100100
int s[N], m[N], cc[N], c[N], q[N], n; long long p[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) {
        cin >> n;
        for (int i=1; i<=n; ++i) p[i] = cc[i] = c[i] = s[i] = m[i] = 0;
        for (int i=1; i<n; ++i) {
            int u, v, w; cin >> u >> v >> w;
            ++c[u]; ++c[v];
            p[u] += v; p[v] += u;
            cc[u] += w; cc[v] += w;
        }
        int ans = 0, head = 0, tail = 0;
        for (int u=1; u<=n; ++u) if (c[u]==1) q[tail++] = u;
        while (head < tail) {
            int u = q[head++], v = p[u], w = cc[u];
            if (w < s[u]) m[u] -= w, s[u] -= w, ans += max(m[u], (s[u]+1) >> 1);
            if (v) {
                s[v] += w; m[v] = max(m[v], w);
                p[v] -= u; cc[v] -= w;
                if (--c[v] == 1) q[tail++] = v;
            }
        }
        cout << "Case #" << kase << ": " << ans << endl;
    }
    return 0;
}