/**
 * UVa11846
 * 找座位
 */

#include <iostream>
using namespace std;

#define min(a, b) (a<b ? a:b)

short n, k; char g[20][20], s[20][20];

bool dfs(short r=0, short c=0, short ch='A') {
    if (c == n) {++r; c=0;}
    while (r<n && c<n && s[r][c] != '.') {
        ++c; if (c == n) {++r; c=0;}
    }
    if (r >= n) return true;
    for (short rr = r, ec = min(n, c+9); rr < n; ++rr)
        for (short cc = c; cc < ec; ++cc) {
            short a = (rr-r+1) * (cc-c+1);
            if (s[rr][cc] != '.' || a>9) {ec = cc; break;}
            short t = 10; bool ok = true;
            for (short i = r; i <= rr && ok; ++i)
                for (short j = c; j <= cc && ok; ++j)
                    if (g[i][j] < 10) t < 10 ? ok = false : t = g[i][j];
            if (!ok || a>t) {ec = cc; break;}
            if (a == t) {
                for (short i = r; i <= rr; ++i) for (short j = c; j <= cc; ++j) s[i][j] = ch;
                if (dfs(r, cc+1, ch+1)) return true;
                for (short i = r; i <= rr; ++i) for (short j = c; j <= cc; ++j) s[i][j] = '.';
            }
        }
    return false;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> k && n && k) {
        for (short r=0; r<n; ++r) {
            for (short c=0; c<n; ++c) {
                s[r][c] = '.'; cin >> g[r][c];
                if (g[r][c] != '.') g[r][c] -= '0';
            }
            s[r][n] = 0;
        }
        dfs();
        for (short i=0; i<n; ++i) cout << s[i] << endl;
    }
    return 0;
}