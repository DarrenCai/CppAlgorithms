/**
 * UVa11882
 * 最大的数
 */

#include <iostream>
#include <cstring>
using namespace std;

char g[15][15], a[31], ans[31], q[30][2]; bool visit[15][15] = {0}, v[15][15];
const short dx[] = {0, 0, -1, 1}, dy[] = {1, -1, 0, 0}; short r, c, m;

short h(short row, short col) {
    int head = -1, tail = 0;
    q[tail][0] = row; q[tail++][1] = col;
    memcpy(v, visit, sizeof(v)); v[row][col] = true;
    while (++head != tail)
        for (short i=0; i<4; ++i) {
            short rr = q[head][0] + dx[i], cc = q[head][1] + dy[i];
            if (rr>=0 && rr<r && cc>=0 && cc<c && g[rr][cc] != '#' && !v[rr][cc])
                q[tail][0] = rr, q[tail++][1] = cc, v[rr][cc] = true;
        }
    return tail;
}

void dfs(short row, short col, short step=0) {
    short hh = h(row, col);
    if (hh + step < m) return;
    a[step] = g[row][col]; a[step+1] = '9'+1; a[step+2] = 0;
    if (hh + step == m && strcmp(a, ans) < 0) return;
    visit[row][col] = true; bool noMore = true;
    for (short i=0; i<4; ++i) {
        short rr = row + dx[i], cc = col + dy[i];
        if (rr>=0 && rr<r && cc>=0 && cc<c && g[rr][cc] != '#' && !visit[rr][cc])
            dfs(rr, cc, step+1), noMore = false;
    }
    visit[row][col] = false;
    if (noMore) {
        a[++step] = 0;
        if (step > m || (step == m && strcmp(ans, a) < 0)) {
            m = step; strcpy(ans, a);
        }
    }
}

int main()
{
    while (cin >> r >> c && r && c) {
        memset(ans, 0, sizeof(ans)); m = 0;
        for (short i=0; i<r; ++i) for (short j=0; j<c; ++j) cin >> g[i][j];
        for (short i=0; i<r; ++i) for (short j=0; j<c; ++j)
            if (g[i][j] != '#') dfs(i, j);
        cout << ans << endl;
    }
    return 0;
}