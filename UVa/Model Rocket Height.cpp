/**
 * UVa1333/LA3147
 * North America - Greater NY 2004
 */

#include <iostream>
#include <cmath>
using namespace std;

#define dtr 0.01745329251994329508887757483
double d, h, a, b, c;

int solve() {
    a = 1/tan(a*dtr); b = 1/tan(b*dtr); c = 1/tan(c*dtr);
    return h + d*sqrt(2/(a*a+c*c-2*b*b)) + .5;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cin >> d >> h;
    while (cin>>a>>b>>c && a>0. && b>0. && c>0.) cout << solve() << endl;
    return 0;
}