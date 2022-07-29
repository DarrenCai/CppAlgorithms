/**
 * UVa1481/LA5052
 * 基因组进化
 * Asia - Tehran 2010
 */

#include <iostream>
using namespace std;

#define N 3020
int b[N], p[N], n;

int solve() {
    int cnt = 0;
    for (int i=0, a; i<n; ++i) cin >> a, p[a] = i;
    for (int i=0; i<n; ++i) {
        cin >> b[i];
        int x = p[b[i]], y = x;
        for (int j=i-1; j>=0; --j) {
            x = min(x, p[b[j]]); y = max(y, p[b[j]]);
            if (y-x == i-j) ++cnt;
        }
    }
    return cnt;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) cout << solve() << endl;
    return 0;
}