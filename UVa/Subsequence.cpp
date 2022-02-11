/**
 * UVa1121
 * ⼦序列
 */

#include <iostream>
using namespace std;

#define N 100100
int a[N], n, s;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin >> n >> s) {
        for (int i=0; i<n; ++i) cin >> a[i];
        int l=0, r=-1, x=0, ans = 0;
        while (x<s && ++r<n) x += a[r];
        if (x >= s) {
            ans = r+1-l;
            while (l < n) {
                x -= a[l++];
                while (x<s && ++r<n) x += a[r];
                if (x < s) break;
                ans = min(ans, r+1-l);
            }
        }
        cout << ans << endl;
    }
    return 0;
}