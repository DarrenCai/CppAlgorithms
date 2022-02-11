/**
 * UVa11549
 * 计算器谜题
 */

#include <iostream>
#include <set>
using namespace std;

long long p[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        short n; long long k, ans; set<long long> s;
        cin >> n >> k; ans = k;
        while (!s.count(k)) {
            s.insert(k);
            k *= k;
            while (k >= p[n]) k /= 10;
            ans = max(ans, k);
        };
        cout << ans << endl;
    }
    return 0;
}