/**
 * UVa1408/LA4018
 * ChengDu 2007
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 9
#define N 50
#define T 19683
int a[N][M], d[N][M][T], p[] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, T}, m, n, kase = 0;

bool check(int a, int b, int c) {
    if (!a || !b || !c || a==b || b==c) return false;
    return a < b ? b < c : b > c;
}

int dp(int i, int j, int s) {
    if (i == n) return 0;
    if (j == m) return dp(i+1, 0, s);
    if (d[i][j][s] >= 0) return d[i][j][s];
    int &r = d[i][j][s], t = i ? a[i-1][j] : 0, l = j ? a[i][j-1] : 0, h = s / p[m-1], b = s % 3, c = a[i][j];
    r = dp(i, j+1, s % p[m-1] * 3) + (c != 0);
    if (c && l && ((!b && c != l) || (b==1 && check(a[i][j-2], l, c))))
        r = min(r, dp(i, j+1, s % p[m-1] * 3 + 1));
    if (c && t && ((!h && c != t && (j+1<m ? s/p[m-2]%3 : 0) != 1) || (h==2 && check(a[i-2][j], t, c))))
        r = min(r, dp(i, j+1, s % p[m-1] * 3 + 2));
    return r;
}

void solve() {
    memset(d, -1, sizeof(d));
    for (int i=0; i<n; ++i) for (int j=0; j<m; ++j) cin >> a[i][j], a[i][j] = max(a[i][j], 0);
    cout << "Case " << ++kase << ": " << dp(0, 0, 0) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m && (m || n)) solve();
    return 0;
}