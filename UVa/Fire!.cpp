/**
 * UVa11624
 * ⼤⽕蔓延的迷宫
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1010
struct grid {int r, c;} q[N*N], qf[N*N]; char s[N][N]; bool vis[N][N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        int r, c, jr, jc, hf = 0, tf = 0, t1 = 0, head = 0, tail = 1, t2 = 1, ans = 1; bool ok = false;
        cin >> r >> c;
        memset(vis, 0, sizeof(vis));
        for (int i=1; i<=r; ++i) {
            cin >> s[i]+1;
            for (int j=1; j<=c; ++j) {
                if (s[i][j] == 'J') {
                    jr = i; jc = j; vis[jr][jc] = true; q[0].r = jr; q[0].c = jc; s[i][j] = '.';
                } else if (s[i][j] == 'F') qf[tf].r = i, qf[tf++].c = j, t1 = tf;
            }
        }
        while (hf < t1) {
            grid t = qf[hf++];
            if (t.r>1 && s[t.r-1][t.c]=='.') {
                s[t.r-1][t.c] = 'F'; qf[tf].r = t.r-1; qf[tf++].c = t.c;
            }
            if (t.c>1 && s[t.r][t.c-1]=='.') {
                s[t.r][t.c-1] = 'F'; qf[tf].r = t.r; qf[tf++].c = t.c-1;
            }
            if (t.r<r && s[t.r+1][t.c]=='.') {
                s[t.r+1][t.c] = 'F'; qf[tf].r = t.r+1; qf[tf++].c = t.c;
            }
            if (t.c<c && s[t.r][t.c+1]=='.') {
                s[t.r][t.c+1] = 'F'; qf[tf].r = t.r; qf[tf++].c = t.c+1;
            }
        }
        t1 = tf;
        while (head < t2) {
            grid t = q[head++];
            if (t.r==1 || t.c==1 || t.r==r || t.c==c) {
                ok = true; break;
            }
            if (t.r>1 && s[t.r-1][t.c]=='.' && !vis[t.r-1][t.c]) {
                q[tail].r = t.r-1; q[tail++].c = t.c; vis[t.r-1][t.c] = true;
            }
            if (t.c>1 && s[t.r][t.c-1]=='.' && !vis[t.r][t.c-1]) {
                q[tail].r = t.r; q[tail++].c = t.c-1; vis[t.r][t.c-1] = true;
            }
            if (t.r<r && s[t.r+1][t.c]=='.' && !vis[t.r+1][t.c]) {
                q[tail].r = t.r+1; q[tail++].c = t.c; vis[t.r+1][t.c] = true;
            }
            if (t.c<c && s[t.r][t.c+1]=='.' && !vis[t.r][t.c+1]) {
                q[tail].r = t.r; q[tail++].c = t.c+1; vis[t.r][t.c+1] = true;
            }
            if (head == t2) {
                while (hf < t1) {
                    grid t = qf[hf++];
                    if (t.r>1 && s[t.r-1][t.c]=='.') {
                        s[t.r-1][t.c] = 'F'; qf[tf].r = t.r-1; qf[tf++].c = t.c;
                    }
                    if (t.c>1 && s[t.r][t.c-1]=='.') {
                        s[t.r][t.c-1] = 'F'; qf[tf].r = t.r; qf[tf++].c = t.c-1;
                    }
                    if (t.r<r && s[t.r+1][t.c]=='.') {
                        s[t.r+1][t.c] = 'F'; qf[tf].r = t.r+1; qf[tf++].c = t.c;
                    }
                    if (t.c<c && s[t.r][t.c+1]=='.') {
                        s[t.r][t.c+1] = 'F'; qf[tf].r = t.r; qf[tf++].c = t.c+1;
                    }
                }
                t1 = tf; t2 = tail; ++ans;
            }
        }
        ok ? (cout << ans << endl) : (cout << "IMPOSSIBLE" << endl);
    }
    return 0;
}