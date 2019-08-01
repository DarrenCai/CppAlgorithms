/**
 * UVa12627
 * 奇怪的气球膨胀
 */

#include <iostream>
using namespace std;

int count(short k, int r) {
    if (k == 0) return 1;
    return r&1 ? count(k-1, r>>1) : count(k-1, r>>1)<<1;
}

long long count(short k, int a, int b) {
    if (a == b) return count(k, a);
    long long s = 0;
    if (a&1) s += count(k, a), ++a;
    if (~b&1) s += count(k, b), --b;
    if (a<=b) s += 3*count(k-1, a/2, b/2);
    return s;
}

int main()
{
    short t, k; cin >> t;
    for (short i=1; i<=t; ++i) {
        int a, b; cin >> k >> a >> b; --a; --b;
        cout << "Case " << i << ": " << count(k, a, b) << endl;
    }
    return 0;
}