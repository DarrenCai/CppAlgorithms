/**
 * UVa1363
 * 约瑟夫的数论问题
 */

#include <iostream>
using namespace std;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int n, k;
    while (cin >> n >> k) {
        long long s = 0; int i=2;
        while (i <= n) {
            int q = k/i, r = k%i;
            long long j = q==0 ? n : min(k/q, n);
            s += (2*r - (j-i)*q)*(j-i+1)/2;
            i = j+1;
        }
        cout << s << endl;
    }
    return 0;
}