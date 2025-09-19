/**
 * UVa524/LA5270
 * 素数环
 * Shanghai 1996
 */

#include <iostream>
using namespace std;

const bool isPrim[] = {false, false, true, true, false, true, false, true, false, false, false, 
                       true, false, true, false, false, false, true, false, true, false, false,
                       false, true, false, false, false, false, false, true, false, true, false};
int a[16], vis[17] = {false}, n, kase = 0;

void dfs(int i = 1) {
    if (i == n) {
        cout << a[0];
        for (int j=1; j<n; ++j) cout << ' ' << a[j];
        cout << endl;
    } else for (int j=2; j<=n; ++j) if (!vis[j] && isPrim[a[i-1]+j] && (i+1 < n || isPrim[j+a[0]])) {
        vis[a[i] = j] = true; dfs(i+1); vis[j] = false;
    }
}

void solve() {
    if (kase++) cout << endl;
    cout << "Case " << kase << ":" << endl;
    dfs();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    a[0] = 1;
    while (cin >> n) solve();
    return 0;
}