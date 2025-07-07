/**
 * UVa1094/LA4789
 * 修筑水道
 * World Finals 2010
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 3001   // 2498
#define R 20
#define C 9
int d[2][2][M], hs[2][M], st[2][2][M], cc[2][2], m, n, kase = 0; char s[R][C+1];
struct node {int x, a; bool c;} ans[R][C][2][M];

int r_t_l(int k, int i) {
    for (int c=1, j=3*m; i<=j; i+=3) {
        int t = k>>i & 7;
        if (t == 1) ++c;
        else if (t == 2 && --c == 0) return k ^ 3<<i;
    }
    return k;
}

int l_t_r(int k, int i) {
    for (int c=1; i>=0; i-=3) {
        int t = k>>i & 7;
        if (t == 2) ++c;
        else if (t == 1 && --c == 0) return k ^ 3<<i;
    }
    return k;
}

int r_t_d(int k, int i) {
    for (int c=1, j=3*m; i<=j; i+=3) {
        int t = k>>i & 7;
        if (t == 1) ++c;
        else if (t == 2 && --c == 0) return k | 3<<i;
    }
    return k;
}

int l_t_d(int k, int i) {
    for (int c=1; i>=0; i-=3) {
        int t = k>>i & 7;
        if (t == 2) ++c;
        else if (t == 1 && --c == 0) return k | 3<<i;
    }
    return k;
}

void update(int s, int v, int t, int x, const node& p, node (&ans)[2][M]) {
    int y = s % M;
    while (hs[x][y] >= 0 && st[t][x][hs[x][y]] != s) y = (y+1) % M;
    if (hs[x][y] < 0) d[t][x][cc[t][x]] = v, st[t][x][cc[t][x]] = s, ans[x][hs[x][y] = cc[t][x]++] = p;
    else if (d[t][x][hs[x][y]] < v) d[t][x][hs[x][y]] = v, ans[x][hs[x][y]] = p;
}

void solve() {
    int ee = 0;
    d[0][0][0] = st[0][0][0] = cc[0][1] = 0; cc[0][0] = 1;
    for (int i=0, c=1; i<n; ++i) {
        cin >> s[i];
        for (int j=0, b=0; j<m; ++j, b+=3, c^=1) {
            memset(hs, -1, sizeof(hs)); cc[c][0] = cc[c][1] = 0;
            for (int x=0; x<2; ++x) for (int a=0; a<cc[c^1][x]; ++a) {
                int e = d[c^1][x][a], k = st[c^1][x][a], l = k>>b & 7, t = k>>b+3 & 7,
                    v = j+1 < m ? 36<<b : 4<<b, y = t && j+1 < m, w = k ^ (t<<3)+l<<b;
                if (s[i][j] == '.') {
                    if (!l && !t) {
                        if (x) update(k, e, c, y, {x, a, false}, ans[i][j]);
                        else if (!i && !j) {
                            if (i+1 < n) update(k | (j+1 < m ? 35 : 3) << b, e+1, c, y, {x, a, true}, ans[i][j]);
                            if (j+1 < m) update(k | 28<<b, e+1, c, y, {x, a, true}, ans[i][j]);
                        } else {
                            update(k, e, c, y, {x, a, false}, ans[i][j]);
                            if (i+1 < n && j+1 < m) update(k | 17<<b, e+1, c, y, {x, a, true}, ans[i][j]);
                        }
                    } else if (!l || !t) {
                        if (l == 4) update(w, e, c, y, {x, a, false}, ans[i][j]);
                        else if (t == 4) update(w, e, c, y, {x, a, false}, ans[i][j]);
                        else {
                            l += t;
                            if (i+1 < n) update(w | (j+1 < m ? 32+l : l) << b, e+1, c, y, {x, a, true}, ans[i][j]);
                            if (j+1 < m) update(w | (l<<3)+4<<b, e+1, c, y, {x, a, true}, ans[i][j]);
                            if (i+1 == n && j+1 == m && l == 3 && e >= ee) ee = e+1, ans[i][j][0][0] = {x, a, true};
                        }
                    } else if (l == 4 || t == 4) {
                        if (l == t && x) update(w, e, c, y, {x, a, false}, ans[i][j]);
                    } else if (l == 2 && t == 1) update(w | v, e+1, c, y, {x, a, true}, ans[i][j]);
                    else if (l == 1 && t == 1) update(r_t_l(w, b+6) | v, e+1, c, y, {x, a, true}, ans[i][j]);
                    else if (l == 2 && t == 2) update(l_t_r(w, b-3) | v, e+1, c, y, {x, a, true}, ans[i][j]);
                    else if (l == 3 && l != t) update((t<2 ? r_t_d(w, b+6) : l_t_d(w, b-3)) | v, e+1, c, y, {x, a, true}, ans[i][j]);
                    else if (t == 3 && l != t) update((l<2 ? r_t_d(w, b+6) : l_t_d(w, b-3)) | v, e+1, c, y, {x, a, true}, ans[i][j]);
                } else if ((!l && !(t&3)) || (!t && !(l&3)) || (l == 4 && t == 4 && x)) update(w, e, c, y, {x, a, false}, ans[i][j]);
            }
        }
        for (int x=0; x<2; ++x) for (int j=0; j<cc[c^1][x]; ++j) st[c^1][x][j] <<= 3;
    }
    for (int i=n-1, x=0, a=0; i>=0; --i) for (int j=m-1; j>=0; --j) {
        const node &t = ans[i][j][x][a];
        if (t.c) s[i][j] = 'C';
        x = t.x; a = t.a;
    }
    cout << "Case " << ++kase << ':' << endl;
    for (int i=0; i<n; ++i) cout << s[i] << endl;
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m && n) solve();
    return 0;
}