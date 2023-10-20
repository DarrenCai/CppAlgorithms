/**
 * UVa11468
 * 子串
 */

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

#define M 102
#define N 22
#define L 24
#define C 62

int idx(char c) {
    return c>96 ? c-61 : (c>64 ? c-55 : c-48);
}

struct node {int ch[C], veto, f;} trie[N*L];
int q[N*L], m, n, c, t, kase; char s[L], ch; double d[N*L][M], p[C];

void insert(const char (&s)[L]) {
    int x = 0;
    for (int i=0; s[i]; ++i) {
        int c = idx(s[i]), &k = trie[x].ch[c];
        if (!k) memset(trie + (k = ++t), 0, sizeof(node));
        x = k;
    }
    trie[x].veto = 1;
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
            trie[u].veto |= trie[f].veto;
        }
    }
}

double dp(int x, int m) {
    double &r = d[x][m];
    if (__builtin_isnan(r)) {
        if (m == 0) return r = 1.;
        r = 0.;
        for (int i=0, u; i<C; ++i) if (p[i]>0. && !trie[u = trie[x].ch[i]].veto) r += p[i]*dp(u, m-1);
    }
    return r;
}

void solve() {
    memset(trie, t=0, sizeof(node)); memset(d, -1, sizeof(d)); memset(p, 0, sizeof(p));
    cin >> n;
    for (int i=1; i<=n; ++i) cin >> s, insert(s);
    cin >> c;
    for (int i=0; i<c; ++i) cin >> ch >> p[idx(ch)];
    getFail();
    cin >> m;
    cout << "Case #" << kase << ": " << dp(0, m) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(6);
    int t; cin >> t;
    for (kase=1; kase<=t; ++kase) solve();
    return 0;
}