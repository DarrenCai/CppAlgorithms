/**
 * UVa1394/LA3882
 * Asia Tokyo 2007
 * 约瑟夫问题的变形
 * Josephus problem
 * int f(int n, int m) {    // 编号从0起
 *     return n==1 ? 0 : (f(n-1, m) + m) % n;
 * }
 * int f(int n, int m) {    // 编号从1起
 *     return n==1 ? 1 : (f(n-1, m)-1 + m) % n + 1;
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