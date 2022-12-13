/**
 * UVa11722
 * 和朋友会面
 */

#include <iostream>
#include <iomanip>
using namespace std;

double solve() {
    int s1, s2, t1, t2, w;
    cin >> s1 >> s2 >> t1 >> t2 >> w;
    if (s1-w >= t2 || s2+w <= t1) return 0.;
    double s = 1., a = 2.*(s2-s1)*(t2-t1);
    if (s2-w > t1) s -= (s2-w-t1)*(s2-w-t1)/a;
    if (s2-w > t2) s += (s2-w-t2)*(s2-w-t2)/a;
    if (s1-w > t1) s += (s1-w-t1)*(s1-w-t1)/a;
    if (s1+w < t2) s -= (t2-w-s1)*(t2-w-s1)/a;
    if (s2+w < t2) s += (t2-w-s2)*(t2-w-s2)/a;
    if (s1+w < t1) s += (t1-w-s1)*(t1-w-s1)/a;
    return s;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(8);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Case #" << kase << ": " << solve() << endl;
    return 0;
}