/**
 * UVa1648
 * 商业中心
 */

#include <iostream>
using namespace std;

#define M 1000000000

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int n, m, u, d, t;
    while (cin >> n >> m) {
        int ans = M;
        for (int i=0; i<m; ++i) {
            cin >> u >> d;
            u += d; t = n*d;
            ans = min(t/u*u + u - t, ans);
        }
        cout << ans << endl;
    }
    return 0;
}