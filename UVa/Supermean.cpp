/**
 * UVa10883
 * 超级平均数
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 50020
long double a[N];

double solve() {
    int n; cin >> n;
    for (int i=0; i<n; ++i) cin >> a[i];
    long double ans = .5*(a[0] + a[n-1]), c = .5;
    for (int i=1, m=(n+1)>>1; i<m; ++i) c = .25*c*(n-i)/i, ans = ((i<<1) == n-1 ? .5 : .25)*ans + c*(a[i] + a[n-1-i]);
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(3);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Case #" << kase << ": " << solve() << endl;
    return 0;
}