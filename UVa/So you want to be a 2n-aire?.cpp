/**
 * UVa10900
 * 你想当2^n元富翁吗?
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(3);
    short n; double t;
    while (cin>>n>>t && n) {
        double d = 1<<n;
        for (int i=n-1; i>=0; --i) {
            double p = (1<<i) / d;
            d = p<=t ? (1+t)/2*d : ((1<<i)*(p-t) + (1+p)/2*d*(1-p))/(1-t);
        }
        cout << d << endl;
    }
    return 0;
}