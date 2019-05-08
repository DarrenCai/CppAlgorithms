/**
 * UVa307
 * 小木棍
 */

#include <iostream>
#include <cstring>
#define min(a, b) (a<b ? a:b)
using namespace std;

short s[51], mini, m, n, ans; int t;

bool dfs(short r, short mx, int tt) {
    if (t % ans) return false;
    if (r == 0) return tt==0 || dfs(ans, m, tt);
    if (s[mx]) {
        --s[mx];
        if (dfs(r-mx, min(r-mx, mx), tt-mx))
            return true;
        ++s[mx];
        if (r == ans || r == mx) return false;
    }
    return mx > mini && dfs(r, mx-1, tt);
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("ou.txt", "w", stdout);
    while (cin >> n && n) {
        mini=50, t = m = 0; memset(s, 0, sizeof(s));
        for (short i=0; i<n; ++i) {
            short x; cin>>x; ++s[x]; t += x;
            if (x > m) m = x; if (x < mini) mini = x;
        }
        for (ans=m; !dfs(ans, m, t) && ans <= (t>>1); ++ans);
        cout << (ans>(t>>1) ? t : ans) << endl;
    }
    return 0;
}