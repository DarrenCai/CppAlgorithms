/**
 * UVa1639
 * 糖果
 * lrj的思路：用对数运算防止double溢出，但即便如此，也需要用long double才行
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(6);
    int n, kase=0; long double p, q;
    while (cin>>n>>p) {
        long double q = 1.-p, pp=log(p), lp=(n+1)*pp, qq=log(q), lq=(n+1)*qq, c=.0, s=n*(exp(lp) + exp(lq));
        for (int i=1; i<n; ++i) c += log(n+i)-log(i), s += (n-i)*(exp(c+lp+i*qq) + exp(c+lq+i*pp));
        cout << "Case " << ++kase << ": " << s << endl;
    }
    return 0;
}