/**
 * URAL1519 Formula 1
 * https://vjudge.net/problem/URAL-1519
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 14001    // 13943
#define N 13
long long d[2][M]; int hs[M], st[2][M], cc[2], m, n; char s[N][N];

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

void update(int s, long long v, int t) {
    int x = s % M;
    while (hs[x] >= 0 && st[t][hs[x]] != s) x = (x+1) % M;
    hs[x] < 0 ? (d[t][cc[t]] = v, st[t][cc[t]] = s, hs[x] = cc[t]++) : d[t][hs[x]] += v;
}

long long solve() {
    int x = 0, y = 0; long long ans = 0;
    for (int i=0; i<n; ++i) {
        cin >> s[i];
        for (int j=0; j<m; ++j) if (s[i][j] == '.') x = i, y = j;
    }
    st[0][0] = 0; d[0][0] = cc[0] = 1;
    for (int i=0, c=1; i<n; ++i) {
        for (int j=0, b=0; j<m; ++j, b+=2, c^=1) {
            memset(hs, -1, sizeof(hs)); cc[c] = 0;
            for (int a=0; a<cc[c^1]; ++a) {
                long long e = d[c^1][a]; int k = st[c^1][a], l = k>>b & 3, t = k>>b>>2 & 3;
                if (s[i][j] == '.') {
                    if (!l && !t) {
                        if (i+1 < n && j+1 < m) update(k | 9<<b, e, c);
                    } else if (!l || !t) {
                        int w = k ^ (t<<2)+l<<b; l += t;
                        if (i+1 < n) update(w | l<<b, e, c);
                        if (j+1 < m) update(w | l<<b<<2, e, c);
                    } else if (l == 1 && t == 2) {
                        if (i == x && j == y && k == (9<<b)) ans += e;
                    } else if (l == 2 && t == 1) update(k ^ 6<<b, e, c);
                    else if (t == 1) update(r_t_l(k ^ 5<<b, b+4), e, c);
                    else update(l_t_r(k ^ 10<<b, b-2), e, c);
                } else if (!l && !t) update(k, e, c);
            }
            if (i == x && j == y) return ans;
        }
        for (int j=0; j<cc[c^1]; ++j) st[c^1][j] <<= 2;
    }
    return 0;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) cout << solve() << endl;
    return 0;
}