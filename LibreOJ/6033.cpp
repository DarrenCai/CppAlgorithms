/**
 * LibreOJ-6033
 * https://vjudge.net/problem/LibreOJ-6033
 * 棋盘游戏
 * 雅礼集训 2017 Day2
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 102
int d[N][N], p[N][N][2], vis[N][N], q[N*N>>1][2], clk, dd, m, n, INF = N*N; char s[N][N];
int ch[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool search() {
    memset(d, -1, sizeof(d)); dd = INF;
    int head = 0, tail = 0;
    for (int i=1, x=0; i<=n; x=(++i&1)^1) for (int j=1; j<=m; ++j) if ((x^=1) && s[i][j]=='.' && p[i][j][0] < 0)
        q[tail][0] = i, q[tail++][1] = j, d[i][j] = 0;
    while (head < tail) {
        int i = q[head][0], j = q[head++][1];
        if (d[i][j] > dd) break;
        for (int k=0; k<4; ++k) {
            int ii = i + ch[k][0], jj = j + ch[k][1];
            if (ii<1 || ii>n || jj<1 || jj>m || s[ii][jj]=='#' || d[ii][jj] >= 0) continue;
            d[ii][jj] = d[i][j] + 1;
            int x = p[ii][jj][0], y = p[ii][jj][1];
            x < 0 ? dd = d[ii][jj] : (d[x][y] = d[ii][jj] + 1, q[tail][0] = x, q[tail++][1] = y);
        }
    }
    return dd != INF;
}

bool dfs(int i, int j) {
    for (int k=0; k<4; ++k) {
        int ii = i + ch[k][0], jj = j + ch[k][1];
        if (ii<1 || ii>n || jj<1 || jj>m || s[ii][jj]=='#' || vis[ii][jj]==clk || d[ii][jj]!=d[i][j]+1) continue;
        vis[ii][jj] = clk;
        if (p[ii][jj][0] >= 0 && d[ii][jj] == dd) continue;
        if (p[ii][jj][0] < 0 || dfs(p[ii][jj][0], p[ii][jj][1])) {
            p[ii][jj][0] = i; p[ii][jj][1] = j; p[i][j][0] = ii; p[i][j][1] = jj;
            return true;
        }
    }
    return false;
}

void solve() {
    for (int i=1; i<=n; ++i) cin >> s[i]+1;
    memset(p, -1, sizeof(p)); memset(vis, -1, sizeof(vis));
    clk = 0;
    while (search()) {
        ++clk;
        for (int i=1, x=0; i<=n; x=(++i&1)^1) for (int j=1; j<=m; ++j) if ((x^=1) && s[i][j]=='.' && p[i][j][0] < 0)
            dfs(i, j);
    }
    memset(vis, 0, sizeof(vis));
    int head = 0, tail = 0;
    for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) if (s[i][j]=='.' && p[i][j][0] < 0)
        q[tail][0] = i, q[tail++][1] = j, vis[i][j] = 1;
    while (head < tail) {
        int i = q[head][0], j = q[head++][1];
        for (int k=0; k<4; ++k) {
            int ii = i + ch[k][0], jj = j + ch[k][1];
            if (ii<1 || ii>n || jj<1 || jj>m || s[ii][jj]=='#') continue;
            int x = p[ii][jj][0], y = p[ii][jj][1];
            if (!vis[x][y]) q[tail][0] = x, q[tail++][1] = y, vis[x][y] = 1;
        }
    }
    cout << tail << endl;
    for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) if (vis[i][j]) cout << i << ' ' << j << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) solve();
    return 0;
}