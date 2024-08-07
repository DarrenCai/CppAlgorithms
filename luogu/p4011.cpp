/**
 * P4011 孤岛营救问题
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define N 11
struct state {int x, y, s;} t;
int d[N][N][1<<N], g[N][N][4], f[N][N], n, m, p, k, s; bool inq[N][N][1<<N];
const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

int solve() {
    memset(f, 0, sizeof(f)); memset(g, -1, sizeof(g)); memset(d, 127, sizeof(d)); memset(inq, 0, sizeof(inq));
    while (k--) {
        int x1, y1, x2, y2, z; cin >> x1 >> y1 >> x2 >> y2 >> z;
        int f = x2 == x1-1 ? 0 : (x2 == x1+1 ? 1 : (y2 == y1-1 ? 2 : 3));
        g[x1][y1][f] = g[x2][y2][f^1] = z;
    }
    cin >> s;
    while (s--) {
        int x, y, z; cin >> x >> y >> z; f[x][y] |= 1<<z;
    }
    int cc = -1; d[1][1][f[1][1]] = 0;
    queue<state> q; q.push({1, 1, f[1][1]});
    while (!q.empty()) {
        t = q.front(); q.pop(); inq[t.x][t.y][t.s] = false;
        for (int i=0; i<4; ++i) if (g[t.x][t.y][i]) {
            int x = t.x+dx[i], y = t.y+dy[i];
            if (x < 1 || y < 1 || x > n || y > m || (g[t.x][t.y][i] > 0 && ~t.s & (1<<g[t.x][t.y][i]))) continue;
            int d1 = d[t.x][t.y][t.s]+1, s = t.s | f[x][y];
            if (d1 < d[x][y][s]) {
                d[x][y][s] = d1;
                if (x==n && y==m) cc = cc < 0 ? d1 : min(cc, d1);
                if (!inq[x][y][s]) q.push({x, y, s}), inq[x][y][s] = true;
            }
        }
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m >> p >> k) cout << solve() << endl;
    return 0;
}