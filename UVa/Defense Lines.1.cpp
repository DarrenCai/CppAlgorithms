/**
 * UVa1471/LA4976
 * 防线
 * CERC 2010
 */

#include <iostream>
#include <set>
using namespace std;

#define N 200050
int h[N] = {0}, a[N] = {0}, b[N], n;

struct cmp {
    bool operator() (int i, int j) const {
        return h[i] < h[j];
    }
};

void solve() {
    cin >> n; b[n] = 1;
    for (int i=1; i<=n; ++i) cin >> h[i], a[i] = h[i]>h[i-1] ? a[i-1]+1 : 1;
    for (int i=n-1; i>0; --i) b[i] = h[i]<h[i+1] ? b[i+1]+1 : 1;
    int ans = 0; set<int, cmp> s; s.insert(0);
    for (int i=1; i<=n; ++i) {
        set<int, cmp>::iterator it = s.lower_bound(i), it1 = it--;
        ans = max(ans, b[i] + a[*it]);
        while (it1 != s.end() && a[i] >= a[*it1]) it1 = s.erase(it1);
        if ((it1 == s.end() || h[i] < h[*it1]) && a[i] > a[*it]) s.insert(i);
    }
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}