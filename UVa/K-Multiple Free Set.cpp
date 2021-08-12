/**
 * UVa11246
 * 选整数
 */

#include <iostream>
using namespace std;

int calc(int k, int n) {
    if (n < k) return n; 
    int x, cnt = k-1;
    for (x=k; x*k<=n; x*=k) cnt = x*k-cnt;
    if (n > x) return cnt + calc(k, n-x);
    return cnt;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        cout << calc(k, n) << endl;
    }
    return 0;
}