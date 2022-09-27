/**
 * UVa1380
 * 一个调度问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define max(a, b) (a>b ? a:b)
#define N 210
short g[N][2][N], gc[N][2], u[N<<1][2], d[N][2], q[N][2], uc, n;

short dp(short i, short f=0) {
    if (d[i][f] > 0) return d[i][f];
    d[i][f] = 1;
    for (short j=0; j<gc[i][f]; ++j) d[i][f] = max(d[i][f], 1+dp(g[i][f][j], f));
    return d[i][f];
}

bool dfs(short i, short f, short m) {
    if (++d[i][f] + d[i][1^f] > m) return true; 
    for (short j=0; j<gc[i][1^f]; ++j) if (dfs(g[i][1^f][j], f, m)) return true;
    return false;
}

short add(short m) {
    short head = 0, tail = -1;
    while (true) {
        for (short i=0; i<uc; ++i) {
            short a = u[i][0], b = u[i][1];
            if (d[a][0]+d[a][1] == m) {
                if (d[a][0] == d[b][0] && d[a][1] == d[b][1]) return 1;
                if (d[a][0] == d[b][0] || d[a][1] == d[b][1]) q[++tail][0] = a, q[tail][1] = b;
            }
        }
        if (head > tail) return 0;
        while (head <= tail) {
            short i = q[head][0], j = q[head++][1];
            if (d[i][0] == d[j][0]) {
                if (dfs(j, 0, m)) return 1;
            } else if (d[i][1] == d[j][1]) {
                if (++d[j][1] + d[j][0] > m) return 1;
            }
        }
    }
    return 0;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (true) {
        short i; cin >> i;
        if (i == 0) return 0;
        uc = n = 0; memset(gc, 0, sizeof(gc)); memset(d, 0, sizeof(d));
        while (i > 0) {
            n = max(n, i);
            short j;
            while (cin >> j && j>0) {
                n = max(n, j);
                char ch = cin.get();
                if (ch == ' ') {
                    u[uc][0] = i; u[uc++][1] = j; u[uc][0] = j; u[uc++][1] = i;
                } else {
                    int f = ch == 'd' ? 0 : 1;
                    g[i][f][gc[i][f]++] = j; g[j][1^f][gc[j][1^f]++] = i;
                    cin.get();
                }
            }
            cin >> i;
        }
        short m = 0;
        for (short i=1; i<=n; ++i) m = max(m, dp(i) + dp(i, 1));
        cout << add(m) + m - 1 << endl;
    }
    return 0;
}