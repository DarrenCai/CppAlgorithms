/**
 * UVa11462
 * 年龄排序
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 111
int c[N], m, n, x;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n && n) {
        memset(c, m = 0, sizeof(c));
        while (n--) cin >> x, m = max(m, x), ++c[x];
        for (int i=0; i<=m; ++i) for (int j=0; j<c[i]; ++j) {
            if (++n) cout << ' ';
            cout << i;
        }
        cout << endl;
    }
    return 0;
}