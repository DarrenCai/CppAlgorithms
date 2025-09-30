/**
 * UVa12180/LA4300
 * 游戏
 * SWERC 2008
 */

#include <iostream>
using namespace std;

struct state {int g[10], c[4], s[2], t; bool f;} s; int m, r, t, x;

int alphabeta(const state &e, int alpha, int beta) {
    if (e.g[m] + e.g[r-1] == x) return e.g[m] - e.g[r-1];
    int k = e.t & 1 ? m+1 : 0; bool g = false;
    for (int i=0; i<m; ++i) if (e.g[k+i]) {
        state f = e; int p = (k+i + e.g[k+i]) % r; f.g[k+i] = 0; g = true;
        for (int j=0, c=e.g[k+i], x=k+i+1; j<c; ++j) ++ f.g[(x+j) % r];
        if (!(f.f = p == k+m)) {
            int q = m+1 - k, s = k + p-q; ++ f.t;
            if (p >= k && p < k+m && e.g[p] == 0 && f.g[t-p]) f.g[k+m] += f.g[p] + f.g[t-p], f.g[p] = f.g[t-p] = 0;
            else if (p >= q && p < q+m && f.g[s] && f.s[e.t & 1] < 3 && e.t - f.c[min(p, s)] > 4) {
                ++ f.s[e.t & 1]; swap(f.g[p], f.g[s]); f.c[min(p, s)] = e.t;
                e.t & 1 ? beta = min(beta, alphabeta(f, alpha, beta)) : alpha = max(alpha, alphabeta(f, alpha, beta));
                if (beta <= alpha) return e.t & 1 ? beta : alpha;
                -- f.s[e.t & 1]; swap(f.g[p], f.g[s]); f.c[min(p, s)] = e.c[min(p, s)];
            }
        }
        e.t & 1 ? beta = min(beta, alphabeta(f, alpha, beta)) : alpha = max(alpha, alphabeta(f, alpha, beta));
        if (beta <= alpha) return e.t & 1 ? beta : alpha;
    }
    if (!g) {
        state f = e; f.f = false; ++f.t;
        e.t & 1 ? beta = min(beta, alphabeta(f, alpha, beta)) : alpha = max(alpha, alphabeta(f, alpha, beta));
    }
    return e.t & 1 ? beta : alpha;
}

void solve() {
    cin >> m; r = m+1 << 1; t = m<<1; x = 0;
    for (int i=0; i<r; ++i) cin >> s.g[i], x += s.g[i];
    cout << alphabeta(s, -15, 15) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t; s.c[0] = s.c[1] = s.c[2] = s.c[3] = -4; s.s[0] = s.s[1] = 0; s.t = 1; s.f = false;
    while (t--) solve();
    return 0;
}