/**
 * UVa11178
 * Morley定理
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void solve() {
    int xa, ya, xb, yb, xc, yc; cin >> xa >> ya >> xb >> yb >> xc >> yc;
    int xu = xb-xa, yu = yb-ya, xv = xc-xb, yv = yc-yb, xw = xa-xc, yw = ya-yc;
    double ab = sqrt(xu*xu + yu*yu), bc = sqrt(xv*xv + yv*yv), ca = sqrt(xw*xw + yw*yw);
    double a = acos(-(xu*xw + yu*yw)/ab/ca)/3, b = acos(-(xu*xv + yu*yv)/ab/bc)/3, c = acos(-(xw*xv + yw*yv)/bc/ca)/3;
    double cosa = cos(a), sina = sin(a), cosb = cos(b), sinb = sin(b), cosc = cos(c), sinc = sin(c);
    double x1 = xv*cosb - yv*sinb, y1 = xv*sinb + yv*cosb, x2 = -xv*cosc - yv*sinc, y2 = xv*sinc - yv*cosc;
    double t = (x2*yv - xv*y2) / (x2*y1 - x1*y2), xd = xb + x1*t, yd = yb + y1*t, xe, ye, xf, yf;
    x1 = xw*cosc - yw*sinc, y1 = xw*sinc + yw*cosc; x2 = -xw*cosa - yw*sina, y2 = xw*sina - yw*cosa;
    t = (x2*yw - xw*y2) / (x2*y1 - x1*y2); xe = xc + x1*t; ye = yc + y1*t;
    x1 = xu*cosa - yu*sina, y1 = xu*sina + yu*cosa; x2 = -xu*cosb - yu*sinb, y2 = xu*sinb - yu*cosb;
    t = (x2*yu - xu*y2) / (x2*y1 - x1*y2); xf = xa + x1*t; yf = ya + y1*t;
    cout << xd << ' ' << yd << ' ' << xe << ' ' << ye << ' ' << xf << ' ' << yf << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(6);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}