/**
 * LA5844/UVa1509
 * Regionals 2011 >> Asia - Daejeon
 */

#include <iostream>
#include <string>
using namespace std;

#define N 26
int a[N], len[N], m, n, k; string s, ls;

int dfs(int curr = 0, int p = 0) {
    if (curr == m) return p == n;
    if (p >= n) return 0;
    int x = s[curr] - 'a';
    if (a[x]<0) {
        a[x] = p;
        for (int &i = len[x] = 1; i<=k; ++i) if (dfs(curr+1, p+i)) return 1;
        a[x] = -1;
    } else {
        for (int i=0, j=a[x]; i<len[x]; ++i) if (ls[i+j] != ls[i+p]) return 0;
        if (dfs(curr+1, p+len[x])) return 1;
    }
    return 0;
}

int solve() {
    cin >> k >> s >> ls;
    m = s.length(); n = ls.length();
    for (int i=0; i<N; ++i) a[i] = -1;
    if (n<m || n>k*m) return 0;
    return dfs();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}