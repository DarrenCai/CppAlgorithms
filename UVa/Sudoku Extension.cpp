/**
 * UVa1461/LA4763
 * 扩展数独
 * Harin 2009
 */

#include <iostream>
using namespace std;

char s[9][9]; bool r[9][9], c[9][9], g[9][9]; int ans;

void dfs(int i = 0, int j = 0) {
    if (j == 9) return dfs(i+1);
    if (i == 9) {
        ++ans;
        return;
    }
    char ch = s[i][j];
    if (ch >= '1' && ch <= '9') return dfs(i, j+1);
    if (ch == '0') {
        for (int v=0; v<9; ++v) if (!r[i][v] && !c[j][v] && !g[i/3*3+j/3][v]) {
            r[i][v] = c[j][v] = g[i/3*3+j/3][v] = true; s[i][j] = '1' + v;
            dfs(i, j+1);
            r[i][v] = c[j][v] = g[i/3*3+j/3][v] = false; s[i][j] = ch;
        }
    } else if (ch == 'e') {
        for (int v=1; v<9; v += 2) if (!r[i][v] && !c[j][v] && !g[i/3*3+j/3][v]) {
            r[i][v] = c[j][v] = g[i/3*3+j/3][v] = true; s[i][j] = '1' + v;
            dfs(i, j+1);
            r[i][v] = c[j][v] = g[i/3*3+j/3][v] = false; s[i][j] = ch;
        }
    } else if (ch == 'o') {
        for (int v=0; v<9; v += 2) if (!r[i][v] && !c[j][v] && !g[i/3*3+j/3][v]) {
            r[i][v] = c[j][v] = g[i/3*3+j/3][v] = true; s[i][j] = '1' + v;
            dfs(i, j+1);
            r[i][v] = c[j][v] = g[i/3*3+j/3][v] = false; s[i][j] = ch;
        }
    } else for (int v=0; v<9; ++v) {
        bool ok = true; int x[81], y[81], t = 0;
        for (int a=0; ok && a<9; ++a) for (int b=0; ok && b<9; ++b) if (s[a][b] == ch) {
            if (r[a][v] || c[b][v] || g[a/3*3+b/3][v]) ok = false;
            else r[a][v] = c[b][v] = g[a/3*3+b/3][v] = true, x[t] = a, y[t++] = b;
        }
        if (ok) {
            for (int a=0; a<t; ++a) s[x[a]][y[a]] = '1' + v;
            dfs(i, j+1);
        }
        while (t--) {
            int a = x[t], b = y[t];
            r[a][v] = c[b][v] = g[a/3*3+b/3][v] = false; s[a][b] = ch;
        }
    }
}

int solve() {
    for (int i=0; i<9; ++i) for (int j=0; j<9; ++j) r[i][j] = c[i][j] = g[i][j] = false, cin >> s[i][j];
    for (int i=0; i<9; ++i) for (int j=0; j<9; ++j) if (s[i][j] >= '1' && s[i][j] <= '9') {
        int v = s[i][j] - '1';
        if (r[i][v] || c[j][v] || g[i/3*3+j/3][v]) return 0;
        r[i][v] = c[j][v] = g[i/3*3+j/3][v] = true;
    }
    ans = 0; dfs();
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}