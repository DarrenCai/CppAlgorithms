/**
 * UVa1356/LA3485
 * 桥上的绳索
 * Hangzhou 2005
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double a;

double f(double x) {
    return sqrt(1 + 4*a*a*x*x);
}

double simpson(double a, double b, double fa, double fb, double fc) {
    return (fa + 4*fc + fb) * (b-a)/6;
}

double asr(double a, double b, double fa, double fb, double fc, double s, double eps) {
    double c = (a+b) / 2, fcl = f((a+c)/2), fcr = f((c+b)/2),
        sl = simpson(a, c, fa, fc, fcl), sr = simpson(c, b, fc, fb, fcr);
    if (abs(sl+sr-s) <= 15*eps) return sl+sr + (sl+sr-s)/15;
    return asr(a, c, fa, fc, fcl, sl, eps/2) + asr(c, b, fc, fb, fcr, sr, eps/2);
}

double parabola_arc_length(double w, double h) {
    a = 4*h/w/w;
    double fa = f(0), fb = f(w/2), fc = f(w/4);
    return 2*asr(0, w/2, fa, fb, fc, simpson(0, w/2, fa, fb, fc), 1e-5);
}

void solve(int kase) {
    int d, h, b, l; cin >> d >> h >> b >> l;
    int n = (b+d-1) / d;
    double low = 0., high = h, ll = double(l) / n, w = double(b) / n;
    while (int(100*low+.5) < int(100*high+.5)) {
        double mid = (low + high) / 2;
        parabola_arc_length(w, h-mid) < ll ? high = mid : low = mid;
    }
    if (kase > 1) cout << endl;
    cout << "Case " << kase << ':' << endl << high << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(2);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) solve(kase);
    return 0;
}