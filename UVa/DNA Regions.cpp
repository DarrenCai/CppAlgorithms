/**
 * UVa1392/LA3716
 * DNA突变区域
 * CERC 2006
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 150200
char s1[N], s2[N]; int n, p;
struct node {
    int i, v;
    bool operator< (int x) const {
        return v < x;
    }
} q[N];

void solve() {
    cin >> s1 >> s2;
    int s = 0, t = 1, ans = 0; q[0].i = q[0].v = 0;
    for (int i=0; i<n; ++i) {
        s += (s1[i] != s2[i]);
        int v = 100*s - p*(i+1);
        if (v > q[t-1].v) q[t].i = i+1, q[t++].v = v;
        else ans = max(ans, i+1 - q[lower_bound(q, q+t, v) - q].i);
    }
    ans ? cout << ans << endl : cout << "No solution." << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n>>p && n) solve();
    return 0;
}