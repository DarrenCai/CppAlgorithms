/**
 * UVa10706
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 65536
#define c(x) (x<10 ? 1 : (x<100 ? 2 : (x<1000 ? 3 : (x<10000 ? 4 : 5))))
int a[N]; long long b[N];

short solve() {
    long long i; cin >> i;
    int x = lower_bound(b, b+N, i) - b;
    i -= b[x-1];
    int y = lower_bound(a, a+N, i) - a;
    i -= a[y-1];
    for (short k = c(y)-i; k>0; --k) y /= 10;
    return y%10;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    a[0] = b[0] = 0; for (int i=1; i<N; ++i)  a[i] = a[i-1] + c(i), b[i] = b[i-1] + a[i];
    short t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}
