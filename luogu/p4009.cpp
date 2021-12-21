/**
 * p4009 汽车加油行驶问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 110
#define K 12
struct node {int x, y, k, d;} q[12000000];
int d[N][N][K], s[N][N], n, k, a, b, c;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> k >> a >> b >> c) {
        for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) cin >> s[i][j];
        memset(d, -1, sizeof(d)); d[0][0][k] = 0; q[0].x = 0; q[0].y = 0; q[0].k=k; q[0].d = 0;
        int head = 0, tail = 1, ans = -1; --n;
        while (head < tail) {
            node &t = q[head++], tt;
            if (t.d > d[t.x][t.y][t.k]) continue;
            if (t.k) {
                if (t.x<n) {
                    tt.x = t.x+1; tt.y = t.y; tt.k = s[tt.x][tt.y] ? k : t.k-1;
                    int &ref = d[tt.x][tt.y][tt.k], dd = t.d + (s[tt.x][tt.y] ? a : 0);
                    if (ref==-1 || dd<ref) ref = dd, tt.d = dd, q[tail++] = tt;
                    if (tt.x==n && tt.y==n) ans = ans==-1 ? ref : min(ans, ref);
                }
                if (t.y<n) {
                    tt.x = t.x; tt.y = t.y+1; tt.k = s[tt.x][tt.y] ? k : t.k-1;
                    int &ref = d[tt.x][tt.y][tt.k], dd = t.d + (s[tt.x][tt.y] ? a : 0);
                    if (ref==-1 || dd<ref) ref = dd, tt.d = dd, q[tail++] = tt;
                    if (tt.x==n && tt.y==n) ans = ans==-1 ? ref : min(ans, ref);
                }
                if (t.x>0) {
                    tt.x = t.x-1; tt.y = t.y; tt.k = s[tt.x][tt.y] ? k : t.k-1;
                    int &ref = d[tt.x][tt.y][tt.k], dd = t.d + (s[tt.x][tt.y] ? a+b : b);
                    if (ref==-1 || dd<ref) ref = dd, tt.d = dd, q[tail++] = tt;
                }
                if (t.y>0) {
                    tt.x = t.x; tt.y = t.y-1; tt.k = s[tt.x][tt.y] ? k : t.k-1;
                    int &ref = d[tt.x][tt.y][tt.k], dd = t.d + (s[tt.x][tt.y] ? a+b : b);
                    if (ref==-1 || dd<ref) ref = dd, tt.d = dd, q[tail++] = tt;
                }
            }
            int &ref = d[t.x][t.y][k], dd = t.d + (s[t.x][t.y] ? a : a+c);
            if (ref==-1 || dd<ref) ref = dd, t.k = k, t.d = dd, q[tail++] = t;
            if (t.x==n && t.y==n) ans = ans==-1 ? ref : min(ans, ref);
        }
        cout << ans << endl;
    }
    return 0;
}