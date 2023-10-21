/**
 * UVa111019
 * 矩阵匹配器
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 1002
#define N 102
#define C 26

struct node {int ch[C], val, f;} trie[N*N];

int c[M][M], g[N][N], q[N*N], m, n, x, y, t; char p[N], s[M][M];

void insert(const char (&s)[N], int v) {
    int u = 0;
    for (int i=0; i<y; ++i) {
        int &k = trie[u].ch[s[i]-'a'];
        if (!k) memset(trie + (k = ++t), 0, sizeof(node));
        u = k;
    }
    if (!trie[u].val) trie[u].val = v;
    for (int i=0, (&e)[N]=g[trie[u].val]; i<x; ++i) if (!e[i]) {
        e[i] = v; break;
    }
}

void getFail() {
    int head = 0, tail = 0;
    for (int i=0, u; i<C; ++i) if (u = trie[0].ch[i]) q[tail++] = u;
    while (head < tail) {
        int x = q[head++];
        for (int i=0; i<C; ++i) {
            int &u = trie[x].ch[i];
            if (!u) {
                u = trie[trie[x].f].ch[i];
                continue;
            }
            q[tail++] = u;
            int &f = trie[u].f = trie[trie[x].f].ch[i];
        }
    }
}

void update(int u, int r, int y) {
    for (int i=0, (&e)[N]=g[trie[u].val]; i<x; ++i) {
        if (!e[i]) break;
        ++c[max(r-e[i]+1, 0)][y];
    }
}

void find(const char (&s)[M], int r) {
    int u = 0;
    for (int i=0; i<n; ++i) {
        u = trie[u].ch[s[i]-'a'];
        if (trie[u].val) update(u, r, i);
    }
}

void solve() {
    memset(trie, t=0, sizeof(node)); memset(g, 0, sizeof(g)); memset(c, 0, sizeof(c));
    cin >> m >> n;
    for (int i=1; i<=m; ++i) cin >> s[i];
    cin >> x >> y;
    for (int i=1; i<=x; ++i) cin >> p, insert(p, i);
    getFail();
    for (int i=1; i<=m; ++i) find(s[i], i);
    int ans = 0;
    for (int r=1, i=m-x+1; r<=i; ++r) for (int j=y-1; j<n; ++j) if (c[r][j] == x) ++ans;
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