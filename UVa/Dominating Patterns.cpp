/**
 * UVa1449/LA4670
 * 出现次数最多的子串
 * Hefei 2009
 */

#include <iostream>
#include <cstring>
#include <map>
using namespace std;

#define M 1000010
#define N 152
#define L 72
#define C 26

int idx(char c) {
    return c-'a';
}

struct node {int ch[C], val, last, f;} trie[N*L];
int q[N*L], cnt[N], n, t; char p[N][L], s[M];

void insert(const char (&s)[L], int v) {
    int x = 0;
    for (int i=0; s[i]; ++i) {
        int c = idx(s[i]), &k = trie[x].ch[c];
        if (!k) memset(trie + (k = ++t), 0, sizeof(node));
        x = k;
    }
    trie[x].val = v;
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
            trie[u].last = trie[f].val ? f : trie[f].last;
        }
    }
}

void update(int x) {
    if (x) ++cnt[trie[x].val], update(trie[x].last);
}

void find(const char (&s)[M]) {
    for (int i=0, x = 0; s[i]; ++i) {
        x = trie[x].ch[idx(s[i])];
        if (trie[x].val) update(x);
        else if (trie[x].last) update(trie[x].last);
    }
}

void solve() {
    memset(trie, t=0, sizeof(node));
    memset(cnt, 0, sizeof(cnt));
    map<string, int> id;
    for (int i=1; i<=n; ++i) {
        cin >> p[i];
        insert(p[i], i);
        id[string(p[i])] = i;
    }
    getFail();
    cin >> s;
    find(s);
    int cc = -1;
    for (int i=1; i<=n; ++i) cc = max(cnt[i], cc);
    cout << cc << endl;
    for (int i=1; i<=n; ++i) if (cnt[id[p[i]]] == cc) cout << p[i] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin>>n && n) solve();
    return 0;
}