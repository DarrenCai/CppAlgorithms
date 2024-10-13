/**
 * UVa10572
 * 黑和白
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 1430
#define N 8
int d[N][2][M], e[N][N][2][2][2][M], p[1<<(3*N-5)], g[N][N], r[M], a[N], b[N], m, n, c, cc, h, t;
struct {int a, b, c, s;} q[M<<9]; struct {int i, c;} ans[M<<9]; bool inq[2][2][2][M]; char s[N][N];

void decode(int x) {
    for (int i=n-1; i>=0; --i) a[i] = x&7, x >>= 3;
}

bool valid(int x) {
    decode(x);
    for (int i=0; i<n; ++i) for (int j=i+2; j<n; ++j) if (a[i] == a[j])
        for (int k=i+1; k<j; ++k) if (a[i] != a[k]) for (int t=j+1; t<n; ++t) if (a[k] == a[t]) return false;
    return true;
}

int rep() {
    for (int i=0, j=0, k; i<n; ++i) {
        for (k=0; k<i; ++k) if (a[k] == a[i]) break;
        if (k == i) b[a[i]] = j++;
    }
    int y = 0;
    for (int i=0; i<n; ++i) y = y<<3 | b[a[i]];
    return y;
}

int rep(int x) {
    decode(x);
    return rep();
}

int fr(int x) {
    for (int i=n-1; i>=0; --i) a[i] = x&1, x >>= 1;
    for (int i=0; i<n; ++i) if ((a[i] && s[0][i]=='#') || (!a[i] && s[0][i]=='o')) return -1;
    int y = 0;
    for (int i=0, j=0; i<n; ++i) y = y<<3 | (i>0 && a[i]!=a[i-1] ? ++j : j);
    return p[y];
}

int fc(int i, int f) {
    int x = f;
    for (int j=1; j<=i; ++j) if (a[j] != a[j-1]) x ^= 1;
    return x;
}

void upd(int a, int b, int c, int s, int d, int &r) {
    inq[a][b][c][s] ? r += d : (r = d, q[t++] = {a, b, c, s}, inq[a][b][c][s] = true);
}

void upd(int a, int s, int d, int &r) {
    if (!r) q[t++] = {a, -1, -1, s};
    r += d;
}

void dfs(int i, int j, int h) {
    if (i) {
        g[i][j] = ans[h].c;
        dfs(j ? i : i-1, j ? j-1 : n-1, ans[h].i);
    } else {
        int c = g[0][0] = q[h].a;
        decode(r[q[h].s]);
        for (int i=1; i<n; ++i) g[0][i] = a[i] != a[i-1] ? c^=1 : c;
    }
}

void gen(int j, int h, int c) {
    if (cc == 0) {
        if (j+1 < n) g[m-1][n-1] = c;
        g[m-1][j] = c; dfs(j ? m-1 : m-2, j ? j-1 : n-1, h);
    }
}

int mx(int x) {
    int r = 0;
    for (int i=n-1; i>=0; --i) r = max(r, x&7), x >>= 3;
    return r;
}

bool check(char c, int x) {
    int ch = c=='.' ? -1 : c=='o';
    return ch < 0 || ch == x;
}

void solve() {
    cin >> m >> n; h = t = cc = 0; memset(d, 0, sizeof(d));
    for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) cin >> s[i][j];
    for (int i=c=0, x=1<<(3*n-5); i<x; ++i) if (valid(i) && rep(i) == i) r[p[i] = c++] = i;
    for (int i=0, x=1<<n, f; i<x; ++i) if ((f = fr(i)) >= 0) d[0][a[0]][f] = 1, q[t++] = {a[0], -1, -1, f};
    for (int i=1, m1=m-1; i<m; ++i) for (int j=0; j<n; ++j) {
        if (j>0 && s[i][j]!='.' && s[i][j]==s[i][j-1] && s[i][j]==s[i-1][j] && s[i][j]==s[i-1][j-1]) {
            cout << 0 << endl; return;
        }
        int t0 = t, ch = s[i][j]=='.' ? -1 : s[i][j]=='o'; memset(inq, 0, sizeof(inq));
        while (h < t0) {
            int c0 = q[h].a, b = q[h].b, c = q[h].c, g = q[h++].s; decode(r[g]);
            int d0 = j ? e[i][j-1][c0][b][c][g] : d[i-1][c0][g], f = fc(j-1, c0), x;
            if (j == n-1) {
                if (f != b || f != c || b != c) {
                    if (f == c && a[j-1] != a[j]) for (int k=0, z=a[j]; k<n; ++k) if (a[k] == z) a[k] = a[j-1];
                    if (ch < 0 || ch == c) {
                        x = p[rep()]; ans[t] = {h-1, c}; upd(c0, x, d0, d[i][c0][x]);
                        if (i == m1 && mx(r[x]) == 1) gen(j, h-1, c), cc += d0;
                    }
                    decode(r[g]); b = 0; for (int k=0; k<n && b<2; ++k) if (a[k]==a[j]) ++b;
                    if (ch != c) {
                        if (b > 1) {
                            if (i == m1 && f != c && mx(r[g]) == 1) cc += d0, gen(j, h-1, 1^c);
                            a[j] = f==c ? n-1 : a[j-1]; x = p[rep()]; ans[t] = {h-1, 1^c}; upd(c0, x, d0, d[i][c0][x]);
                        } else if (i == m1 && f != c && check(s[m1][j], f)) {
                            a[j] = a[j-1];
                            if (rep() == 0) gen(j, h-1, 1^c), cc += d0;
                        }
                    }
                } else if (ch != f) {
                    if (i == m1 && r[g] == 0) gen(j, h-1, 1^c), cc += d0;
                    a[j] = n-1; x = p[rep()]; ans[t] = {h-1, 1^c}; upd(c0, x, d0, d[i][c0][x]);
                }
            } else if (j > 0) {
                int y = a[j+1]==a[j] ? c : 1^c;
                if (f != b || f != c || b != c) {
                    if (f == c && a[j-1] != a[j]) for (int k=0, z=a[j]; k<n; ++k) if (a[k] == z) a[k] = a[j-1];
                    if (ch < 0 || ch == c) x = p[rep()], ans[t] = {h-1, c}, upd(c0, c, y, x, d0, e[i][j][c0][c][y][x]);
                    decode(r[g]); b = 0; for (int k=0; k<n && b<2; ++k) if (a[k]==a[j]) ++b;
                    if (ch != c) {
                        if (b > 1) {
                            a[j] = f==c ? n-1 : a[j-1]; x = p[rep()]; ans[t] = {h-1, 1^c}; upd(c0, c, y, x, d0, e[i][j][c0][c][y][x]);
                        } else if (i == m1 && c != y && c != f && j+2==n && check(s[m1][n-1], f)) {
                            a[j] = a[j+1] = a[j-1];
                            if (rep() == 0) gen(j, h-1, 1^c), cc += d0;
                        }
                    }
                } else if (ch != f) a[j] = n-1, x = p[rep()], ans[t] = {h-1, 1^c}, upd(c0, c, y, x, d0, e[i][j][c0][c][y][x]);
            } else {
                c = a[1]==a[0] ? f : 1^f; b = 1;
                for (int k=1; k<n; ++k) if (a[k]==a[0]) ++b;
                if (ch < 0 || ch == f) ans[t] = {h-1, f}, upd(f, f, c, g, d0, e[i][j][f][f][c][g]);
                if (ch != f) {
                    if (b > 1) a[0] = n-1, b = 1^f, x = p[rep()], ans[t] = {h-1, b}, upd(b, f, c, x, d0, e[i][j][b][f][c][x]);
                    else if (i == m1 && f != c && n==2 && check(s[m1][1], c)) gen(j, h-1, 1^f), cc += d0;
                }
            }
        }
    }
    cout << cc << endl;
    if (cc) {
        for (int i=0; i<m; ++i) {
            for (int j=0; j<n; ++j) cout << (g[i][j] ? 'o' : '#');
            cout << endl;
        }
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}