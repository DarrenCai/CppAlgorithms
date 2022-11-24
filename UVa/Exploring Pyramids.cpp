/**
 * UVa1362/LA3516
 * 多叉树遍历
 * NEERC 2005
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 1000000000
#define N 305
char s[N]; int f[N][N];

long long dp(int i, int j) {
    int &r = f[i][j];
    if (r >= 0) return r;
    if (i >= j) return r = 1;
    if (s[i]!=s[j] || j==i+1) return r = 0;
    r = dp(i+1, j-1);
    for (int k=i+2; k<j; ++k) if (s[i]==s[k] && s[i+1]==s[k-1]) r = (r + dp(i+1, k-1) * dp(k, j)) % M;
    return r;
}

int solve() {
    int n = strlen(s);
    memset(f, -1, sizeof(f));
    return dp(0, n-1);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> s) cout << solve() << endl;
    return 0;
}