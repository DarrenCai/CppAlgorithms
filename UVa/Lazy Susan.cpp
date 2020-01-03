/**
 * UVa1620
 * 懒惰的苏珊
 * n为奇数且逆序数也为奇数则无解，否则有解
 */

#include <iostream>
using namespace std;

#define N 505
short a[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        short n, s=0; cin >> n;
        for (short i=0; i<n; ++i) cin >> a[i];
        if (n&1) for (short i=n-2; i>=0; --i) for (short j=i+1; j<n; ++j) if (a[i] > a[j]) ++s;
        cout << (n&1 && s&1 ? "impossible" : "possible") << endl;
    }
    return 0;
}