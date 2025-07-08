/**
 * poj1739 Tony's Tour
 * http://poj.org/problem?id=1739
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 401   // 341
int d[2][M], hs[M], st[2][M], cc[2], m, n; char b;

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

int r_t_d(int k, int i) {
    for (int c=1, j=m<<1; i<=j; i+=2) {
        int t = k>>i & 3;
        if (t == 1) ++c;
        else if (t == 2 && --c == 0) return k | 3<<i;
    }
    return k;
}

int l_t_d(int k, int i) {
    for (int c=1; i>=0; i-=2) {
        int t = k>>i & 3;
        if (t == 2) ++c;
        else if (t == 1 && --c == 0) return k | 3<<i;
    }
    return k;
}

void update(int s, int v, int t) {
    int x = s % M;
    while (hs[x] >= 0 && st[t][hs[x]] != s) x = (x+1) % M;
    hs[x] < 0 ? (d[t][cc[t]] = v, st[t][cc[t]] = s, hs[x] = cc[t]++) : d[t][hs[x]] += v;
}

int solve() {
    int ans = 0;
    st[0][0] = 0; d[0][0] = cc[0] = 1;
    for (int i=0, c=1; i<n; ++i) {
        for (int j=0, f=0; j<m; ++j, f+=2, c^=1) {
            memset(hs, -1, sizeof(hs)); cc[c] = 0; cin >> b;
            for (int a=0; a<cc[c^1]; ++a) {
                int e = d[c^1][a], k = st[c^1][a], l = k>>f & 3, t = k>>f>>2 & 3, w =  k ^ (t<<2)+l<<f;
                if (b == '.') {
                    if (!l && !t) {
                        if (i+1 < n && j+1 < m) update(k | 9<<f, e, c);
                        else if (i+1 == n && !j) update(k | 12<<f, e, c);
                    } else if (!l || !t) {
                        l += t;
                        if (i+1 < n) update(w | l<<f, e, c);
                        if (j+1 < m) update(w | l<<f<<2, e, c);
                        if (i+1 == n && !j && l < 3) update(r_t_d(w, f+4), e, c);
                        if (i+1 == n && j+1 == m && l == 3) ans += e;
                    } else if (l == 2 && t == 1) update(w, e, c);
                    else if (l == 1 && t == 1) update(r_t_l(w, f+4), e, c);
                    else if (l == 2 && t == 2) update(l_t_r(w, f-2), e, c);
                    else if (l == 3 && l != t) update(t<2 ? r_t_d(w, f+4) : l_t_d(w, f-2), e, c);
                    else if (t == 3 && l != t) update(l<2 ? r_t_d(w, f+4) : l_t_d(w, f-2), e, c);
                } else if (!l && !t) update(k, e, c);
            }
        }
        for (int j=0; j<cc[c^1]; ++j) st[c^1][j] <<= 2;
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m && n) cout << solve() << endl;
    return 0;
}