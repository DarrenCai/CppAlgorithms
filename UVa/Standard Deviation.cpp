/**
 * UVa10886
 * 标准差
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

unsigned long long seed;
long double gen() {
    static const long double Z = (long double)1.0 / (1LL<<32);
    seed >>= 16;
    seed &= (1ULL << 32) - 1;
    seed *= seed;
    return seed * Z;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(5);
    short t; cin >> t;
    for (short kase=1; kase<=t; ++kase) {
        int n; cin >> n >> seed;
        long double s1 = 0., s2 = 0.;
        for (int i=0; i<n; ++i) {
            long double v = gen();
            if (v == 0.) break;
            s1 += v*v; s2 += v;
        }
        s2 /= n;
        cout << "Case " << "#" << kase << ": " << sqrt(s1/n - s2*s2) << endl;
    }
    return 0;
}