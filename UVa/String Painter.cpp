/**
 * UVa1437/LA4394
 * 字符串“刷子”
 * Chengdu 2008
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 110
int d[N], f[N][N][26]; char a[N], b[N];

int dp(int i, int j, int k) {
    int &r = f[i][j][k];
    if (r >= 0) return r;
    if (i > j) return r = 0;
    if (i == j) return r = 'a'+k != b[i];
    int m = N;
    for (int t=i, k1=b[i]-'a'; t<=j; ++t) if (b[t] == b[i]) m = min(m, dp(i+1, t, k1) + dp(t+1, j, k));
    return r = ('a'+k != b[i]) + m;
}

int solve() {
    int n = strlen(a);
    memset(f, -1, sizeof(f)); d[n] = 0;
    for (int i=n-1; i>=0; --i) {
        if (a[i] != b[i]) {
            d[i] = 1 + d[i+1];
            for (int j=i+1, k=b[i]-'a'; j<n; ++j) if (b[j] == b[i]) d[i] = min(d[i], 1 + dp(i+1, j-1, k) + d[j+1]);
        } else d[i] = d[i+1];
    }
    return d[0];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> a >> b) cout << solve() << endl;
    return 0;
}