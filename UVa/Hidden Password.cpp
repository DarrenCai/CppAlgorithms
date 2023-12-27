/**
 * UVa1314/LA2755
 * SEERC 2003
 * 字符串的最小表示法：https://www.cnblogs.com/jiamian/p/11236830.html
 */

#include <iostream>
using namespace std;

#define N 100100
int n; char s[N];

void solve() {
    cin >> n >> s;
    int i=0, j=1, k=0;
    while (i<n && j<n && k<n) {
        int d = s[(i+k)%n] - s[(j+k)%n];
        if (d) {
            d<0 ? j = max(j+k+1, i+1) : i = max(i+k+1, j+1);
            k = 0;
        } else ++k;
    }
    cout << min(i, j) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}