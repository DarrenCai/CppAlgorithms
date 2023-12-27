/**
 * UVa1399/LA3907
 * Seoul 2007
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1002
#define L 53
#define C 26
int ch[N*L][C], f[N*L], last[N*L], vis[N*L], d[N*L], q[N*L], m, n, t; char s[L], ans[N*L];

int dfs(int u) {
    if (d[u] >= -1) return d[u];
    d[u] = ans[u] = 0;
    for (int i=0, v; i<m; ++i) {
        if (!(v = ch[u][i]) || vis[v]) return d[u] = -1;
        vis[v] = 1;
        int x = last[v] ? 0 : dfs(v);
        vis[v] = 0;
        if (x < 0) return d[u] = -1;
        if (++x >= d[u]) ans[u] = i+'A', d[u] = x;
    }
    return d[u];
}

void print(int u) {
    int v = ch[u][ans[u]-'A'];
    if (last[v]) {
        cout << endl; return;
    }
    cout << ans[u]; print(v);
}

void solve() {
    memset(ch[0], t = 0, sizeof(ch[0])); memset(vis, 0, sizeof(vis)); d[0] = -2;
    cin >> m >> n;
    while (n--) {
        cin >> s;
        int x = 0;
        for (int i=0; s[i]; ++i) {
            int c = s[i]-'A', &r = ch[x][c];
            if (!r) memset(ch[r = ++t], 0, sizeof(ch[0])), f[r] = last[r] = 0, d[r] = -2;
            x = r;
        }
        last[x] = 1;
    }
    int head = 0, tail = 0;
    for (int i=0, u; i<C; ++i) if (u = ch[0][i]) q[tail++] = u;
    while (head < tail) {
        int x = q[head++];
        for (int i=0; i<C; ++i) {
            int &u = ch[x][i];
            if (!u) {
                u = ch[f[x]][i];
                continue;
            }
            q[tail++] = u; f[u] = ch[f[x]][i];
        }
    }
    int d = dfs(0);
    if (d > 1) print(0);
    else cout << "No" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}