/**
 * UVa11549
 * 计算器谜题
 */

#include <iostream>
using namespace std;

int p[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000}, n, k;

int next(long long k) {
    k *= k;
    while (k >= p[n]) k/=10;
    return k;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        cin >> n >> k;
        int ans = k, k1 = k, k2 = k;
        do {
            k1 = next(k1);
            k2 = next(k2); ans = max(ans, k2);
            k2 = next(k2); ans = max(ans, k2);
        } while (k1 != k2);
        cout << ans << endl;
    }
    return 0;
}