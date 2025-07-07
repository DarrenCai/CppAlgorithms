/**
 * UVa1501/LA5762
 * 修建长城
 * Chengdu 2011
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 2001   // 1670
#define N 9
int d[2][M], hs[M], st[2][M], cc[2], m, n, kase = 0; char s[N][N+1]; bool f[N+1][N+1];

int r_t_l(int k, int i) {
    for (int c=1, j=m<<1; i<=j; i+=2) {
        int t = k>>i & 3;
        if (t == 1) ++c;
        else if (t == 2 && --c == 0) return k ^ 3<<i;
    }
    return k;
}

int l_t_r(int k, int i) {
    for (int c=1; i>=0; i-=2) {
        int t = k>>i & 3;
        if (t == 2) ++c;
        else if (t == 1 && --c == 0) return k ^ 3<<i;
    }
    return k;
}

int inner(int k, int i) {
    int c = 0;
    for (int j=0; j<i; j+=2) {
        int t = k>>j & 3;
        if (t == 1) ++c;
        else if (t == 2) --c;
    }
    return c&1;
}

void update(int s, int v, int t) {
    int x = s % M;
    while (hs[x] >= 0 && st[t][hs[x]] != s) x = (x+1) % M;
    if (hs[x] < 0) d[t][cc[t]] = v, st[t][cc[t]] = s, hs[x] = cc[t]++;
    else if (v < d[t][hs[x]]) d[t][hs[x]] = v;
}

int solve() {
    cin >> n >> m;
    for (int i=0; i<n; ++i) cin >> s[i];
    for (int i=0; i<=m; ++i) s[n][i] = ' ';
    for (int i=n; i>=0; --i) for (int j=m; j>=0; --j)
        f[i][j] = i<n && (j<m ? f[i][j+1] || s[i][j]=='o' : f[i+1][0]);
    int ans = -1; ++m; d[0][0] = st[0][0] = 0; cc[0] = 1;
    for (int i=0, c=1; i<=n; ++i) {
        for (int j=0, b=0; j<m; ++j, b+=2, c^=1) {
            memset(hs, -1, sizeof(hs)); cc[c] = 0;
            for (int a=0; a<cc[c^1]; ++a) {
                int e = d[c^1][a], k = st[c^1][a], l = k>>b & 3, t = k>>b>>2 & 3, r = inner(k, b);
                bool g = (!r && s[i][j]!='x') || (r && s[i][j]!='o'), h = (r && s[i][j]!='x') || (!r && s[i][j]!='o');
                if (!l && !t) {
                    if (i<n && j+1<m && g) update(k | 9<<b, e+2, c);
                    if (h) update(k, e, c);
                } else if (!l || !t) {
                    int w = k ^ (t<<2)+l<<b; l += t;
                    if (i<n && g) update(w | l<<b, e+1, c);
                    if (j+1<m && h) update(w | l<<b<<2, e+1, c);
                } else if (l == 1 && t == 2) {
                    if (k == (9<<b) && !f[i][j] && (ans<0 || ans>e)) ans = e;
                } else if (l == 2 && t == 1) {
                    if (h) update(k ^ 6<<b, e, c);
                } else if (t == 1) {
                    if (h) update(r_t_l(k ^ 5<<b, b+4), e, c);
                } else if (h) update(l_t_r(k ^ 10<<b, b-2), e, c);
            }
        }
        for (int j=0; j<cc[c^1]; ++j) st[c^1][j] <<= 2;
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) cout << "Case #" << k << ": " << solve() << endl;
    return 0;
}