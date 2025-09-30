/**
 * UVa12418
 * 999 游戏
 */

#include <iostream>
#include <set>
using namespace std;

#define M 10
int g[M][38], c[M] = {0}, cc[512], u[M], v[M], d[M], m, n, cnt; bool ans[512];
struct node {
    int s[10], v;
    bool operator< (const node &r) const {
        if (v != r.v) return v < r.v;
        for (int i=0; i<n; ++i) if (s[i] != r.s[i]) return s[i] < r.s[i];
        return false;
    }
} q[200000], s;

void print(int x) {
    cout << ' ';
    for (int i=8; i>=0; --i) if (x & 1<<i) cout << 9-i;
}

void solve() {
    for (int i=0; i<512; ++i) ans[i] = false;
    for (int i=0; i<m; ++i) cin >> u[i] >> v[i] >> d[i], --u[i], --v[i];
    q[0].v = 0; q[0].s[0] = 511; for (int i=1; i<n; ++i) q[0].s[i] = 0;
    set<node> vis; vis.insert(q[0]);
    for (int h=cnt=0, t=1; h<t; ++h) {
        if (q[h].s[n-1]) {
            ans[q[h].s[n-1]] = true; cnt = max(cnt, cc[q[h].s[n-1]]);
            if (cnt == 9) break;
        }
        for (int i=0; i<m; ++i) if (~q[h].v & 1<<i && q[h].s[u[i]]) {
            if (d[i]) {
                for (int k=d[i], j=c[k]-1; j>=0; --j) if ((g[k][j] & q[h].s[u[i]]) == g[k][j]) {
                    s = q[h]; s.s[u[i]] = q[h].s[u[i]] ^ g[k][j]; s.s[v[i]] |= g[k][j]; s.v |= 1<<i;
                    if (!vis.count(s)) q[t++] = s, vis.insert(s);
                }
            } else for (int f=q[h].s[u[i]], ss=f; ss > 0; ss = (ss-1)&f) {
                s = q[h]; s.s[u[i]] = f ^ ss; s.s[v[i]] |= ss;
                if (!vis.count(s)) q[t++] = s, vis.insert(s);
            }
        }
    }
    cout << cnt;
    for (int i=511; i>0; --i) if (ans[i] && cc[i] == cnt) print(i);
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=1; i<512; ++i) {
        int k = 0, s = 0;
        for (int j=0; j<9; ++j) if (i & (1<<j)) ++k, s += 9-j;
        cc[i] = k;
        if (k > 2 && k < 6) {
            while (s > 9) s = s/10 + s%10;
            g[s][c[s]++] = i;
        }
    }
    while (cin >> n >> m) solve();
    return 0;
}