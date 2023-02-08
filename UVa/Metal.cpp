/**
 * UVa1425/LA4258
 * 金属
 * Seoul 2008
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 52
long long f[N][N][N]; bool g[N][N], h[N][N];

struct point {
    long long x, y;
    bool operator< (const point& rhs) const {
        return x < rhs.x;
    }
    bool rel(const point& la, const point& lb, bool up = true) const {
        long long a = (lb.x - x) * la.y + (x - la.x) * lb.y, b = (lb.x - la.x) * y;
        return up ? a < b : a > b;
    }
} s[N];

long long solve() {
    int n; cin >> n;
    for (int i=0; i<n; ++i) cin >> s[i].x >> s[i].y;
    sort(s, s + n--);
    for (int i=0; i<n; ++i) for (int j=i+1; j<=n; ++j) {
        g[i][j] = h[i][j] = true;
        for (int k=i+1; k<j; ++k) 
            g[i][j] = g[i][j] && s[k].rel(s[i], s[j]), h[i][j] = h[i][j] && s[k].rel(s[i], s[j], false);
    }
    for (int i=0; i<=n; ++i) {
        f[i][0][i] = f[i][i][0] = 1;
        for (int j=1; j<i; ++j) {
            f[i][j][i] = f[i][i][j] = 0;
            for (int k=0; k<j; ++k) {
                if (g[k][j+1]) f[i][j][i] += f[j][j][k];
                if (h[k][j+1]) f[i][i][j] += f[j][k][j];
            }
        }
    }
    long long ans = 0;
    for (int i=0; i<n; ++i) if (h[i][n]) ans += f[n][i][n];
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}