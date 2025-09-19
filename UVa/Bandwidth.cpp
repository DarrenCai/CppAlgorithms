/**
 * UVa140/LA5570
 * 带宽
 * NWERC 1992
 */

#include <iostream>
using namespace std;

const int m = 8; int id[26], a[m], t, ans; char s[90], ch[m]; bool c[m][m], f[26];

void dfs(int i = 0, int w = -1) {
    if (i == t) {
        ans = w; for (int j=0; j<t; ++j) s[j] = ch[a[j]];
    } else for (int j=0; j<t; ++j) if (!f[j]) {
        int x = w;
        for (int k=0; k<i; ++k) if (c[a[k]][j]) x = max(x, i-k);
        if (x < ans) {
            f[a[i] = j] = true;
            dfs(i+1, x);
            f[j] = false;
        }
    }
}

void solve() {
    for (int i=0; i<26; ++i) f[i] = false;
    for (int i=0; s[i]; ++i) if (s[i] >= 'A' && s[i] <= 'Z') f[s[i]-'A'] = true;
    for (int i=t=0; i<26; ++i) if (f[i]) id[i] = t, ch[t++] = 'A'+i;
    for (int i=0; i<t; ++i) for (int j=0; j<t; ++j) c[i][j] = false;
    for (int i=0; s[i]; ++i) if (s[i] == ':') {
        int u = id[s[i-1]-'A'];
        for (int j=i+1; s[j]; ++j) {
            if (s[j] == ';') break;
            int v = id[s[j]-'A'];
            c[u][v] = c[v][u] = true;
        }
    }
    ans = m; for (int i=0; i<t; ++i) f[i] = false;
    dfs();
    for (int i=0; i<t; ++i) cout << s[i] << ' ';
    cout << "-> " << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> s && s[0] != '#') solve();
    return 0;
}