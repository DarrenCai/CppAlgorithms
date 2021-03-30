/**
 * UVa11971
 * 多边形
 */

#include <iostream>
using namespace std;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    for (short kase=1; kase<=t; ++kase) {
        int n; short k; cin >> n >> k;
        for (n=k+1; (n&1)==0; n>>=1, --k);
        long long d = 1ll << k;
        cout << "Case #" << kase << ": " << (d-n) << '/' << d << endl;
    }
    return 0;
}