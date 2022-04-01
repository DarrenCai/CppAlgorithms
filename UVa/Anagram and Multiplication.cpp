/**
 * UVa10825
 * 神奇的乘法
 */

#include <iostream>
#include <set>
using namespace std;

#define M 7
short a[M], m, n;

bool dfs(short i = 1) {
    if (i == m) {
        long long x = 1; short s = 0; for (i=0; i<m; ++i) x *= n, s += a[i];
        x = s*(x-1)/(n-1); s = m*(m+1)/2;
        if (x % s) return false;
        x /= s;
        for (i=2; i<=m; ++i) {
            long long y = i*x; set<short> ss; for (short j=0; j<m; ++j) ss.insert(a[j]);
            for (short j=0; j<m; ++j) ss.erase(y%n), y /= n;
            if (y>0 || !ss.empty()) return false;
        }
        for (i=m-1; i>=0; --i) a[i] = x%n, x/=n;
        return true;
    }
    int x = (i+1)*a[0], y = min(x+i, n-1);
    for (a[i] = max(a[i-1]+1, x); a[i] <= y; ++a[i]) if (dfs(i+1)) return true;
    return false;
}

void solve() {
    for (a[0] = (n-1)/m; a[0]>0; --a[0]) if (dfs()) {
        cout << a[0];
        for (short i=1; i<m; ++i) cout << ' ' << a[i];
        cout << endl;
        return;
    }
    cout << "Not found." << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>m>>n && m) solve();
    return 0;
}
