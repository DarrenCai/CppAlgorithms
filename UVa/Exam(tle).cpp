/**
 * UVa1655
 * 考试
 */

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    long long n; int kase = 0;
    while (cin >> n) {
        long long ans = 0, s = sqrt(n);
        for (long long i=1; i<=s; ++i) {
            long long v = n/i, t = sqrt(v);
            for (long long j=1; j<=t; ++j) ans += v/j;
            for (long long j = v/t == t ? t-1 : t; j>0; --j) ans += j * (v/j - v/(j+1));
        }
        for (long long i = n/s == s ? s-1 : s; i>0; --i) {
            long long c = n/i - n/(i+1), t = sqrt(i);
            for (long long j=1; j<=t; ++j) ans += i/j*c;
            for (long long j = i/t == t ? t-1 : t; j>0; --j) ans += j * (i/j - i/(j+1)) * c;
        }
        cout << "Case " << ++kase << ": " << ans << endl;
    }
    return 0;
}