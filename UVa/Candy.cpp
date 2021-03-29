/**
 * UVa1639
 * 糖果
 * 注意：要防止double溢出
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(6);
    int n, kase=0; double p, q;
    while (cin>>n>>p) {
        double q=1.-p, c=1., sp=n*p*p, sq=n*q*q, pq=p*q; short t = 0;
        for (int i=1; i<n; ++i) {
            c *= pq*(n+i)/i;
            if (max(c, max(sp, sq)) > 1e200) c /= 1e100, sp /= 1e100, sq /= 1e100, ++t;
            if (max(c, max(sp, sq)) < 1e100 && t) c *= 1e100, sp *= 1e100, sq *= 1e100, --t;
            sp = (sp+c*p*(n-i))*p;
            sq = (sq+c*q*(n-i))*q;
        }
        cout << "Case " << ++kase << ": " << sp + sq << endl;
    }
    return 0;
}