/**
 * UVa11609
 * 组队
 */

#include <iostream>
using namespace std;

#define M 1000000007

long long pow2(int n) {
    if (n == 0) return 1;
    long long r = pow2(n>>1);
    r = r*r % M;
    return n&1 ? r*2%M : r;
}

int solve() {
    int n; cin >> n;
    return n*pow2(n-1)%M;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Case #" << kase << ": " << solve() << endl;
    return 0;
}