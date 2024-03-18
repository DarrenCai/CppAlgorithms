/**
 * UVa1506/LA5836
 * 田径接力赛
 * Fuzhou 2011
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

#define N 10010
int s[N], t[N], a[N], m, n, d;
bool cmp(int i, int j) {
    return s[i] > s[j] || (s[i]==s[j] && t[i]<t[j]);
}

double solve() {
    long long l, w, minS = 50000, minT, sum = 0; cin >> n >> d >> l >> w;
    for (int i=m=0; i<n; ++i) {
        cin >> s[i] >> t[i]; w -= d*s[i]; sum += d*t[i]; a[i] = i;
        if (s[i] < minS || (s[i] == minS && t[i] < minT)) minS = s[i], minT = t[i];
    }
    l -= n*d;
    if (l < 0 || w < 0 || minS*l > w) return -1.;
    if (l == 0) return sum;
    if (minS*l == w) return sum + minT*l;
    sort(a, a+n, cmp);
    for (int i=1; i<n; ++i) if (s[a[i]] < s[a[m]]) {
        while (m>=0 && t[a[i]] <= t[a[m]]) --m;
        a[++m] = a[i];
    }
    if (s[a[0]]*l <= w) return sum + t[a[0]]*l;
    double ans = 5e9; int k = 0; while (k<m && s[a[k]]*l>w) ++k;
    for (int i=m; i>=k; --i) for (int j=0; j<k; ++j) {
        double x = (w - s[a[i]]*l) / double(s[a[j]] - s[a[i]]);
        ans = min(ans, t[a[j]]*x + t[a[i]]*(l-x));
    }
    return ans + sum;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(2);
    int t; cin >> t;
    while (t--) {
        double s = solve();
        s < 0. ? cout << "No solution" << endl : cout << s << endl;
    }
    return 0;
}