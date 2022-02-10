/**
 * UVa12097
 * 派
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define N 10020
int n, f; double s[N], mx;

double solve() {
    double low = .0003, high = mx;
    while (low <= high) {
        double mid = (low+high)/2; int c = 0;
        for (int i=0; i<n; ++i) c += s[i]/mid;
        c<f ? high = mid-0.0001 : low = mid+0.0001;
    }
    return high;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(4);
    int t; cin >> t;
    while (t--) {
        cin >> n >> f; ++f; mx = 0;
        for (int i=0; i<n; ++i) cin >> s[i], s[i] = M_PI*s[i]*s[i], mx = max(mx, s[i]);
        cout << solve() << endl;
    }
    return 0;
}