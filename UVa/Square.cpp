/**
 * UVa10364
 * 正方形
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

short s[25], n; int ans; bool visit[25];

bool dfs(int r, short k=3, short f=n-1) {
    if (r == 0) return k==1 || dfs(ans, k-1, n-1);
    if (!visit[f] && s[f]<=r && !(f+1<n && !visit[f+1] && s[f]==s[f+1])) {
        visit[f] = true;
        if (dfs(r-s[f], k, f-1)) return true;
        visit[f] = false;
        if (r == ans || r == s[f]) return false;
    }
    return f>0 && dfs(r, k, f-1);
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int k; cin >> k;
    while (k--) {
        int t = 0; memset(visit, 0, 25); cin >> n;
        for (short i=0; i<n; ++i) {
            cin >> s[i]; t += s[i];
        }
        ans = t >> 2;
        if (t != ans<<2) cout << "no" << endl;
        else {
            sort(s, s+n);
            if (s[n-1] > ans) cout << "no" << endl;
            else cout << (dfs(ans) ? "yes" : "no") << endl;
        }
    }
    return 0;
}