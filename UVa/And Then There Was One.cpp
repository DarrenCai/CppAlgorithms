/**
 * UVa1394
 * 约瑟夫问题的变形
 * Josephus problem
 * int f(int n, int m) {
 *     return n==1 ? 1 : (f(n-1, m) + m-1) % n + 1;
 * }
 */

#include <iostream>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int n, m, k;
    while (cin>>n>>k>>m && n) {
        int ans = 0; for (int i=2; i<=n; ++i) ans = (ans + k) % i;
        ans = ((m-k+ans) % n + n) % n;
        cout << ans+1 << endl;
    }
    return 0;
}