/**
 * UVa1365/LA3525
 * 西部枪手
 * CERC 2005
 */

#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

#define N 100010
int x[N], z[N], a[N], m, n; long long y[N], u;
struct cmp {
    bool operator() (int i, int j) const {
        return x[i] != x[j] ? x[i] < x[j] : y[i] < y[j]; 
    }
};
set<int, cmp> s;

bool cmpz(int i, int j) {
    return z[i] > z[j];
}

void add(int i) {
    set<int, cmp>::iterator it = s.upper_bound(i), nex = it--, pre = it; long long yn = y[*nex];
    if (y[i] <= yn) return;
    while (y[*it] <= y[i]) u -= (x[*it] - x[*--pre]) * (y[*it] - y[*nex]), nex = s.erase(it--);
    u += (x[i] - x[*it]) * (y[i] - yn); s.insert(i);
}

void solve() {
    a[0] = y[n+1] = 0; x[n+1] = N;
    for (int i=1; i<=n; ++i) cin >> x[i] >> y[i] >> z[i], a[i] = i;
    sort(a, a+n+1, cmpz);
    s.clear(); s.insert(0); s.insert(n+1);
    long long ans = 0, q = m * (long long)m;
    for (int i=u=0, t=m; i<n; t = z[a[i]]) {
        while (i<n && z[a[i]] >= t) add(a[i++]);
        ans += (q - u) * (t - z[a[i]]);
    }
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    x[0] = z[0] = 0; y[0] = N;
    while (cin>>n>>m && n) solve();
    return 0;
}