/**
 * UVa10047
 * 独轮车
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 31
struct grid {int x, y, c, d;} q[N*N*20]; char s[N][N]; bool vis[N][N][5][4];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int m, n, kase = 0;
    while (cin >> m >> n && m) {
        memset(vis, 0, sizeof(vis));
        int head = 0, tail = 1, tt = 1, tx, ty, ans = 0; bool ok = false;
        for (int i=1; i<=m; ++i) {
            cin >> s[i]+1;
            for (int j=1; j<=n; ++j) {
                if (s[i][j] == 'S') {
                    q[0].x = i; q[0].y = j; q[0].c = 0; q[0].d = 0; vis[i][j][0][0] = true;
                } else if (s[i][j] == 'T') tx = i, ty = j;
            }
        }
        while (head < tail) {
            const grid& t = q[head++];
            if (t.x==tx && t.y==ty && !t.c) {ok=true; break;}
            if (t.x>1 && !t.d && s[t.x-1][t.y]!='#' && !vis[t.x-1][t.y][q[tail].c = (t.c+1)%5][0]) {
                q[tail].x = t.x-1; q[tail].y = t.y; vis[t.x-1][t.y][q[tail].c][0] = true; q[tail++].d = 0;
            }
            if (t.y>1 && t.d==1 && s[t.x][t.y-1]!='#' && !vis[t.x][t.y-1][q[tail].c = (t.c+1)%5][1]) {
                q[tail].x = t.x; q[tail].y = t.y-1; vis[t.x][t.y-1][q[tail].c][1] = true; q[tail++].d = 1;
            }
            if (t.x<m && t.d==2 && s[t.x+1][t.y]!='#' && !vis[t.x+1][t.y][q[tail].c = (t.c+1)%5][2]) {
                q[tail].x = t.x+1; q[tail].y = t.y; vis[t.x+1][t.y][q[tail].c][2] = true; q[tail++].d = 2;
            }
            if (t.y<n && t.d==3 && s[t.x][t.y+1]!='#' && !vis[t.x][t.y+1][q[tail].c = (t.c+1)%5][2]) {
                q[tail].x = t.x; q[tail].y = t.y+1; vis[t.x][t.y+1][q[tail].c][3] = true; q[tail++].d = 3;
            }
            int d = (t.d+1)&3;
            if (!vis[t.x][t.y][t.c][d])
                q[tail].x = t.x, q[tail].y = t.y, vis[t.x][t.y][q[tail].c = t.c][d] = true, q[tail++].d = d;
            d = (t.d+3)&3;
            if (!vis[t.x][t.y][t.c][d])
                q[tail].x = t.x, q[tail].y = t.y, vis[t.x][t.y][q[tail].c = t.c][d] = true, q[tail++].d = d;
            if (head == tt) tt = tail, ++ans;
        }
        if (kase++) cout << endl;
        cout << "Case #" << kase << endl;
        ok ? (cout << "minimum time = " << ans << " sec" << endl) : (cout << "destination not reachable" << endl);
    }
    return 0;
}