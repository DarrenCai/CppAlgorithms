/**
 * UVa11404
 * 回文子序列
 */

#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#define N 1010
char s[N]; int d[N][N]; string ans[N][N]; bool vis[N][N];

const string& build(int i, int j) {
    string& r = ans[i][j];
    if (vis[i][j]) return r;
    vis[i][j] = true;
    if (i > j) return r = "";
    if (i == j) return r = s[i];
    if (s[i] == s[j]) return r = s[i] + build(i+1, j-1) + s[i];
    if (d[i+1][j] > d[i][j-1]) return r = build(i+1, j);
    if (d[i][j-1] > d[i+1][j]) return r = build(i, j-1);
    return r = min(build(i+1, j), build(i, j-1));
} 

void solve() {
    memset(vis, 0, sizeof(vis));
    int n = strlen(s);
    for (int i=0; i<n; ++i) d[i][i] = 1;
    for (int i=1; i<n; ++i) d[i-1][i] = s[i-1]==s[i] ? 2 : 1;
    for (int l=3; l<=n; ++l) for (int i=n-l, j=n-1; i>=0; --i, --j)
        d[i][j] = s[i]==s[j] ? 2 + d[i+1][j-1] : max(d[i+1][j], d[i][j-1]);
    cout << build(0, n-1) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>s) solve();
    return 0;
}