/**
 * UVa1355/LA3406
 * Bingo游戏
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define M 4
#define INF 17
short c[M][M][M], cc[M][M], s[INF], ans, p, m, n;

void get(short i, short b) {
    if (b == 2*m+1) for (short j=0; j<m; ++j) cc[i][j] = c[i][j][j];
    else if (b == 2*m) for (short j=0; j<m; ++j) cc[i][j] = c[i][j][m-1-j];
    else if (b < m) for (short j=0; j<m; ++j) cc[i][j] = c[i][b][j];
    else for (short j=0; j<m; ++j) cc[i][j] = c[i][j][b-m];
}

bool find(short v) {
    short i = lower_bound(s, s+n, v) - s;
    return i>=0 && s[i]==v;
}

bool bingo(short i, short r) {
    short j;
    for (j=0; j<m; ++j) if (c[i][j][j]==r || !find(c[i][j][j])) break;
    if (j == m) return true;
    for (j=0; j<m; ++j) if (c[i][j][m-1-j]==r || !find(c[i][j][m-1-j])) break;
    if (j == m) return true;
    for (short k=0; k<m; ++k) {
        for (j=0; j<m; ++j) if (c[i][k][j]==r || !find(c[i][k][j])) break;
        if (j == m) return true;
        for (j=0; j<m; ++j) if (c[i][j][k]==r || !find(c[i][j][k])) break;
        if (j == m) return true;
    }
    return false;
}

bool cnt(short i, short r) {
    for (short j=0; j<m; ++j) if (cc[i][j] == r) return true;
    return false;
}

bool check(short i, short r) {
    if (bingo(i, r)) return false;
    bool b = true;
    for (short j=0; j<i; ++j) {
        if (cnt(j, r)) {
            if (bingo(j, r)) return false;
            b = false;
        } else {
            if (!b) return false;
        }
    }
    return true;
}

bool check(short t) {
    for (short i=n=0; i<t; ++i) for (short j=0; j<m; ++j) s[n++] = cc[i][j];
    sort(s, s+n);
    n = unique(s, s+n) - s;
    for (short i=0; i<m; ++i) {
        if (check(t-1, cc[t-1][i])) {
            if (t == p) ans = min(ans, n);
            return true;
        }
    }
    return false;
}

void dfs(short i = 0) {
    for (short b=2*m+1; b>=0; --b) {
        get(i, b);
        if (check(i+1) && i+1<p) dfs(i+1);
    }
}

short solve() {
    for (short i=0; i<p; ++i) for (short j=0; j<m; ++j) for (short k=0; k<m; ++k) cin >> c[i][j][k];
    ans = INF;
    dfs();
    return ans == INF ? 0 : ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>p>>m && p) cout << solve() << endl;
    return 0;
}