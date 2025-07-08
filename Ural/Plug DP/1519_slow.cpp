/**
 * URAL1519 Formula 1
 * https://vjudge.net/problem/URAL-1519
 */

#include <iostream>
#include <unordered_map>
using namespace std;

#define N 13
int m, n; char s[N][N];

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

long long solve() {
    long long ans = 0; int x = 0, y = 0; unordered_map<int, long long> d[2]; d[0][0] = 1;
    for (int i=0; i<n; ++i) {
        cin >> s[i];
        for (int j=0; j<m; ++j) if (s[i][j] == '.') x = i, y = j;
    }
    for (int i=0, c=1; i<n; ++i) {
        for (int j=0, b=0; j<m; ++j, b+=2, c^=1) {
            d[c].clear();
            for (unordered_map<int, long long>::iterator it = d[c^1].begin(); it != d[c^1].end(); ++it) {
                long long e = it->second; int k = it->first, l = k>>b & 3, t = k>>b>>2 & 3;
                if (s[i][j] == '.') {
                    if (!l && !t) {
                        if (i+1 == n || j+1 == m) continue;
                        int w = k | 9<<b; d[c].count(w) ? d[c][w] += e : d[c][w] = e;
                    } else if (!l || !t) {
                        int w = k ^ (t<<2)+l<<b, w1 = w | l+t<<b<<2; l += t;
                        if (i+1 < n) d[c].count(w | l<<b) ? d[c][w | l<<b] += e : d[c][w | l<<b] = e;
                        if (j+1 < m) d[c].count(w1) ? d[c][w1] += e : d[c][w1] = e;
                    } else if (l == 1 && t == 2) {
                        if (i == x && j == y && k == (9<<b)) ans += e;
                    } else if (l == 2 && t == 1) {
                        int w = k ^ 6<<b; d[c].count(w) ? d[c][w] += e : d[c][w] = e;
                    } else if (t == 1) {
                        int w = r_t_l(k ^ 5<<b, b+4); d[c].count(w) ? d[c][w] += e : d[c][w] = e;
                    } else {
                        int w = l_t_r(k ^ 10<<b, b-2); d[c].count(w) ? d[c][w] += e : d[c][w] = e;
                    }
                } else if (!l && !t) d[c].count(k) ? d[c][k] += e : d[c][k] = e;
            }
            if (i == x && j == y) return ans;
        }
        unordered_map<int, long long> dd = d[c^1]; d[c^1].clear();
        for (unordered_map<int, long long>::iterator it = dd.begin(); it != dd.end(); ++it)
            d[c^1][it->first << 2] = it->second;
    }
    return 0;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) cout << solve() << endl;
    return 0;
}