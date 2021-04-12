/**
 * UVa1643
 * 角度和正方形
 */

#include <iostream>
#include <iomanip>
using namespace std;

double x[2], y[2], s, l, t;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(3);
    short n;
    while (cin>>n && n) {
        cin >> x[0] >> y[0] >> x[1] >> y[1];
        t = s = 0;
        while (n--) cin >> l, s += l, t -= l*l;
        l = x[0]*y[1] - x[1]*y[0];
        if (l < 0.) l *= -1.;
        cout << (t + s*s*(x[0]+y[0])*(x[1]+y[1])/l)/2. << endl;
    }
    return 0;
}