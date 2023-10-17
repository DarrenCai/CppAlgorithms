/**
 * UVa1401/LA3942
 * 背单词
 * Nanjing 2007
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 20071027
#define L 400010
#define N 102
char s[L], w[N]; int d[L], n, t, kase = 0;
struct node {int c[26], f;} trie[L];

int dfs(int c = 0) {
    if (d[c] >= 0) return d[c];
    d[c] = c==n;
    for (int i=c+1, k=0; i<=n && k<=t; ++i) {
        k = trie[k].c[s[i]-'a'];
        if (!k) return d[c];
        if (trie[k].f) d[c] = (d[c] + dfs(c + trie[k].f)) % M;
    }
    return d[c];
}

void solve() {
    cin >> n; t = 0; memset(&(trie[0]), 0, sizeof(node)); memset(d, -1, sizeof(d));
    while (n--) {
        cin >> w;
        for (int i=0, x=0; ;) {
            int &k = trie[x].c[w[i]-'a'];
            if (!k) memset(&(trie[k = ++t]), 0, sizeof(node));
            if (!w[++i]) {
                trie[k].f = i;
                break;
            }
            x = k;
        }
    }
    n = strlen(s+1);
    dfs();
    cout << "Case " << ++kase << ": " << d[0] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> s+1) solve();
    return 0;
}