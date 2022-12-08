/**
 * UVa1482/LA5059
 * 石子游戏
 * Jakarta 2010
 */

#include <iostream>
using namespace std;

long long SG(long long x) {
    if (x == 1) return 0;
    return x&1 ? SG(x>>1) : x>>1;
}

long long solve() {
    long long c = 0; int n; cin >> n;
    while (n--) {
        long long x; cin >> x;
        c ^= SG(x);
    }
    return c;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) cout << (solve() ? "YES" : "NO") << endl;
    return 0;
}