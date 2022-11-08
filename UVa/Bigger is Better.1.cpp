/**
 * UVa12105/LA3782
 * 越大越好
 * Xi'an 2006
 */

#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#define N 110
#define M 3010
string d[N][M], s[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
bool vis[N][M]; int c[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6}, n, m, kase = 0;

void update(int i, int j, const string& s) {
    if (!vis[i][j]) d[i][j] = s, vis[i][j] = true;
    else if (s.size() > d[i][j].size() || (s.size() == d[i][j].size() && d[i][j] < s)) d[i][j] = s;
}

void solve() {
    memset(vis, 0, sizeof(vis));
    for (int i=1; i<10; ++i) if (c[i] <= n) update(c[i], i%m, s[i]);
    for (int i=1; i<=n; ++i) for (int j=0; j<m; ++j) if (vis[i][j])
        for (int k=0, x; k<10; ++k) if ((x = i+c[k]) <= n) update(x, (j*10+k)%m, d[i][j]+s[k]);
    string ans = "-1";
    for (int i=1; i<=n; ++i) if (vis[i][0]) {
        const string& s = d[i][0];
        if (ans[0] == '-' || s.size() > ans.size() || (s.size() == ans.size() && ans < s)) ans = s;
    }
    if (n >= c[0] && ans[0] == '-') ans = s[0];
    cout << "Case " << ++kase << ": " << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n>>m && n) solve();
    return 0;
}