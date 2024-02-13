/**
 * UVa11524
 * 内切圆
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void solve() {
    double r, m1, n1, m2, n2, m3, n3; cin >> r >> m1 >> n1 >> m2 >> n2 >> m3 >> n3;
    double a = n1/m1*(m2+n2)/m2, b = (m3+n3)/n3, c = (m1+n1)/m1, v = (b*b+c*c-a*a)/b/c/2;
    cout << r*r*sqrt((1+v)/(1-v))*((m1+n1)/m1 + m3/n3) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(4);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}