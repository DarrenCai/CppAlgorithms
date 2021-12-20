/**
 * p4011 孤岛营救问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 10
struct node {int x, y, s;} q[N*N*(1<<2*N)];
int d[N][N][1<<N], w[N][N][4], s[N][N], m, n, p, k;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m >> p >> k) {
        memset(d, -1, sizeof(d)); memset(w, -1, sizeof(w)); memset(s, 0, sizeof(s));
        while (k--) {
            int x1, y1, x2, y2, g, d; cin >> x1 >> y1 >> x2 >> y2 >> g;
            --x1; --y1; --x2; --y2; d = y1==y2 ? (x1>x2 ? 0 : 3) : (y1>y2 ? 1 : 2);
            w[x1][y1][d] = w[x2][y2][3-d] = g>0 ? 1<<--g : 0;
        }
        cin >> k;
        while (k--) {
            int x, y, g; cin >> x >> y >> g;
            s[--x][--y] |= 1<<--g;
        }
        int head = 0, tail = 1, ans = -1;
        q[0].x = 0; q[0].y = 0; q[0].s = s[0][0]; d[0][0][s[0][0]] = 0;
        while (head < tail) {
            node &t = q[head++], tt;
            int g = w[t.x][t.y][0];
            if (t.x>0 && (g<0 || t.s&g)) {
                tt.x = t.x-1; tt.y = t.y; tt.s = t.s | s[tt.x][t.y];
                int dd = d[t.x][t.y][t.s]+1, &ref = d[tt.x][t.y][tt.s];
                if (ref<0 || dd<ref) ref = dd, q[tail++] = tt;
                if (tt.x==n-1 && t.y==m-1) ans = ans==-1 ? ref : min(ans, ref);
            }
            g = w[t.x][t.y][3];
            if (t.x+1<n && (g<0 || t.s&g)) {
                tt.x = t.x+1; tt.y = t.y; tt.s = t.s | s[tt.x][t.y];
                int dd = d[t.x][t.y][t.s]+1, &ref = d[tt.x][t.y][tt.s];
                if (ref<0 || dd<ref) ref = dd, q[tail++] = tt;
                if (tt.x==n-1 && t.y==m-1) ans = ans==-1 ? ref : min(ans, ref);
            }
            g = w[t.x][t.y][1];
            if (t.y>0 && (g<0 || t.s&g)) {
                tt.x = t.x; tt.y = t.y-1; tt.s = t.s | s[t.x][tt.y];
                int dd = d[t.x][t.y][t.s]+1, &ref = d[t.x][tt.y][tt.s];
                if (ref<0 || dd<ref) ref = dd, q[tail++] = tt;
                if (t.x==n-1 && tt.y==m-1) ans = ans==-1 ? ref : min(ans, ref);
            }
            g = w[t.x][t.y][2];
            if (t.y+1<m && (g<0 || t.s&g)) {
                tt.x = t.x; tt.y = t.y+1; tt.s = t.s | s[t.x][tt.y];
                int dd = d[t.x][t.y][t.s]+1, &ref = d[t.x][tt.y][tt.s];
                if (ref<0 || dd<ref) ref = dd, q[tail++] = tt;
                if (t.x==n-1 && tt.y==m-1) ans = ans==-1 ? ref : min(ans, ref);
            }
        }
        cout << ans << endl;
    }
    return 0;
}