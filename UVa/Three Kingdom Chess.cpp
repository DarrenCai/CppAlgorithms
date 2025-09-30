/**
 * UVa1495/LA5715
 * Beijing 2011
 */

#include <iostream>
using namespace std;

struct state {int x[2][6], y[2][6], b[2][6], c[2][6]; int t[2];} e; int g[6][6], inf = 0x7fffffff, s[3], m, n, k, t;

bool check(int x, int y, int u, int r, int c) {
    int dx = abs(x - r), dy = abs(y - c);
    return u > 1 ? dx+dy < 3 : (u < 1 ? dx<2 && dy<2 : dx+dy<2);
}

bool check(const state &e, int c, int i, int x, int y) {
    if (g[x][y] > 1 || (g[x][y] == 1 && c == 1)) return false;
    for (int j=e.t[i]-1; j>=0; --j) if (x == e.x[i][j] && y == e.y[i][j]) return false;
    return true;
}

void dec(int b, int c, state &e, int i, int j) {
    int u = e.c[i][j], cc = c == u ? b : ((c<1 && u>1) || (c>1 && u==1) || (c==1 && u<1) ? b<<1 : b>>1);
    if (e.b[i][j] <= cc) {
        for (int k=j+1; k<e.t[i]; ++k)
            e.x[i][u=k-1] = e.x[i][k], e.y[i][u] = e.y[i][k], e.b[i][u] = e.b[i][k], e.c[i][u] = e.c[i][k];
        --e.t[i];
    } else e.b[i][j] -= cc;
}

int alphabeta(const state &e, int t, int alpha, int beta, int p = -1, int x = 0, int y = 0, int c = 0) {
    if (t == k || e.t[0] == 0 || e.t[1] == 0) {
        int v = 0;
        for (int i=e.t[0]-1; i>=0; --i) v += e.b[0][i];
        for (int i=e.t[1]-1; i>=0; --i) v -= e.b[1][i];
        return v;
    } else if (p < 0) {
        for (int i=e.t[t&1]-1; i>=0; --i) {
            int v = alphabeta(e, t, alpha, beta, i);
            t&1 ? beta = min(beta, v) : alpha = max(alpha, v);
            if (beta <= alpha) return t&1 ? beta : alpha;
        }
        int v = alphabeta(e, t+1, alpha, beta);
        t&1 ? beta = min(beta, v) : alpha = max(alpha, v);
    } else {
        int px = e.x[t&1][p], py = e.y[t&1][p], u = e.c[t&1][p]; bool ok = true; 
        for (int i=e.t[t&1]-1; ok && i>=0; --i) if (p != i && px == e.x[t&1][i] && py == e.y[t&1][i]) ok = false;
        if (ok) {
            for (int i=e.t[~t&1]-1; i>=0; --i) if (check(px, py, u, e.x[~t&1][i], e.y[~t&1][i])) {
                state f = e; dec(e.b[t&1][p], e.c[t&1][p], f, ~t&1, i); int v = alphabeta(f, t+1, alpha, beta);
                t&1 ? beta = min(beta, v) : alpha = max(alpha, v);
                if (beta <= alpha) return t&1 ? beta : alpha;
            }
            if (c > 0) {
                int v = alphabeta(e, t+1, alpha, beta);
                t&1 ? beta = min(beta, v) : alpha = max(alpha, v);
                if (beta <= alpha) return t&1 ? beta : alpha;
            }
        }
        if (c < s[u]) {
            if (px > 1 && (px-1 != x || py != y) && check(e, u, ~t&1, px-1, py)) {
                state f = e; f.x[t&1][p] = px - 1; int v = alphabeta(f, t, alpha, beta, p, px, py, c+1);
                t&1 ? beta = min(beta, v) : alpha = max(alpha, v);
                if (beta <= alpha) return t&1 ? beta : alpha;
            }
            if (px < n && (px+1 != x || py != y) && check(e, u, ~t&1, px+1, py)) {
                state f = e; f.x[t&1][p] = px + 1; int v = alphabeta(f, t, alpha, beta, p, px, py, c+1);
                t&1 ? beta = min(beta, v) : alpha = max(alpha, v);
                if (beta <= alpha) return t&1 ? beta : alpha;
            }
            if (py > 1 && (px != x || py-1 != y) && check(e, u, ~t&1, px, py-1)) {
                state f = e; f.y[t&1][p] = py - 1; int v = alphabeta(f, t, alpha, beta, p, px, py, c+1);
                t&1 ? beta = min(beta, v) : alpha = max(alpha, v);
                if (beta <= alpha) return t&1 ? beta : alpha;
            }
            if (py < m && (px != x || py+1 != y) && check(e, u, ~t&1, px, py+1)) {
                state f = e; f.y[t&1][p] = py + 1; int v = alphabeta(f, t, alpha, beta, p, px, py, c+1);
                t&1 ? beta = min(beta, v) : alpha = max(alpha, v);
                if (beta <= alpha) return t&1 ? beta : alpha;
            }
        }
    }
    return t&1 ? beta : alpha;
}

int solve() {
    for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) cin >> g[i][j];
    cin >> t >> s[0] >> s[1] >> s[2]; e.t[0] = e.t[1] = 0;
    while (t--) {
        int x, y, a, b, c; cin >> x >> y >> a >> b >> c;
        int &r = e.t[a]; e.x[a][r] = x; e.y[a][r] = y; e.b[a][r] = b; e.c[a][r++] = c;
    }
    return alphabeta(e, 0, -inf, inf);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m >> k && n) cout << solve() << endl;
    return 0;
}