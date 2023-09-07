/**
 * UVa1487/LA5096
 * 体积
 * Harbin 2010
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double r, h;

double f(double x) {
    if (2*x < h) {
        if (2*r > h) return 2*((acos(x/r) - acos(h/2/r)) * r*r + x*sqrt(r*r-x*x)) + h*sqrt(r*r-h*h/4);
        return 2*acos(x/r)*r*r + 2*x*sqrt(r*r-x*x);
    }
    return 2*h*sqrt(r*r - x*x);
}

double simpson(double a, double b) {
    double c = (a+b)/2;
    return (f(a) + 4*f(c) + f(b))*(b-a)/6;
}

double asr(double l, double r, double s, double eps) {
    double m = (l+r)/2, s1 = simpson(l, m), s2 = simpson(m, r), e = (s1+s2-s)/15.;
    if (abs(e) < eps) return s1+s2+e;
    return asr(l, m, s1, eps/2) + asr(m, r, s2, eps/2);
}

double solve() {
    double x = min(r, h/2);
    return 2*M_PI*r*r*h - 2*asr(0, x, simpson(0, x), 1e-6);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(4);
    while (cin >> r >> h) cout << solve() << endl;
    return 0;
}