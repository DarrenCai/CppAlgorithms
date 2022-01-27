/**
 * UVa11292
 * 勇者⽃恶龙
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 20200
int a[N], b[N], n, m;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n>>m && n) {
        long long ans = 0; int h = 0;
        for (int i=0; i<n; ++i) cin >> a[i];
        for (int i=0; i<m; ++i) cin >> b[i];
        sort(a, a+n); sort(b, b+m);
        for (int i=0; i<m; ++i) if (b[i] >= a[h]) {
            ans += b[i];
            if (++h == n) break;
        }
        h < n ? cout << "Loowater is doomed!" << endl : cout << ans << endl;
    }
    return 0;
}