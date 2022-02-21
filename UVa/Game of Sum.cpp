/**
 * UVa10891
 * Sum游戏
 */

#include <iostream>
using namespace std;

#define N 110
int a[N], n; long long d[N][N], s[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    s[0] = 0;
    while (cin>>n && n) {
        for (int i=1; i<=n; ++i) cin >> a[i], s[i] = s[i-1] + a[i];
        for (int l=1; l<=n; ++l) for (int i=n-l+1; i>0; --i) {
            long long v = s[i+l-1] - s[i-1], &ref = d[i][i+l-1] = v;
            for (int ll=1; ll<l; ++ll) ref = max(ref, v-min(d[i][i+ll-1], d[i+ll][i+l-1]));
        }
        cout << 2*d[1][n] - s[n] << endl;
    }
    return 0;
}