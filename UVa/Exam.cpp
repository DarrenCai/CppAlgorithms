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
        long long ans = 0;
        for (long long i=pow(n+.5l, 1.l/3); i>0; --i) for (long long j=sqrt(.5l+n/i); j>=i; --j)
            ans += i<j ? 6*(n/i/j-j)+3 : 3*(n/i/j-j)+1;
        cout << "Case " << ++kase << ": " << ans << endl;
    }
    return 0;
}