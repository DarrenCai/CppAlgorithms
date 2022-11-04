/**
 * UVa1336/LA3181
 * 修缮长城
 * CERC 2004
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 1010
struct node {
    long long x, d;
    bool operator< (const node &rhs) const {
        return x < rhs.x;
    }
} s[N];
bool cmp(const long long &x, const node &v) {
    return x < v.x;
}
long long d[N][N][2], c, x, v; int n;

void solve() {
    long long ans = 0, dd = 0;
    for (int i=0; i<n; ++i) cin >> s[i].x >> c >> s[i].d, ans += c*v, dd += s[i].d;
    sort(s, s+n);
    int k = upper_bound(s, s+n, x, cmp) - s;
    if (k == 0) {
        for (int i=0; i<n; ++i) ans += s[i].d*(s[i].x-x);
    } else if (k == n) {
        for (int i=n-1; i>=0; --i) ans += s[i].d*(x-s[i].x);
    } else {
        int t = k-1;
        d[t][t][0] = d[t][t][1] = dd*(x - s[t].x);
        d[k][k][0] = d[k][k][1] = dd*(s[k].x - x);
        c = dd - s[t].d;
        for (int i=t-1; i>=0; --i) {
            d[i][t][0] = d[i+1][t][0] + (s[i+1].x-s[i].x)*c;
            d[i][t][1] = d[i][t][0] + (s[t].x-s[i].x)*(c -= s[i].d);
        }
        c = dd - s[k].d;
        for (int i=k+1; i<n; ++i) {
            d[k][i][1] = d[k][i-1][1] + (s[i].x-s[i-1].x)*c;
            d[k][i][0] = d[k][i][1] + (s[i].x-s[k].x)*(c -= s[i].d);
        }
        for (int i=t; i>=0; --i) {
            c = dd;
            for (int j=k; j<n; ++j) {
                d[i][j][0] = min(d[i+1][j][0] + (s[i+1].x-s[i].x)*(c-s[j].d), d[i+1][j][1] + (s[j].x-s[i].x)*(c-s[j].d));
                d[i][j][1] = min(d[i][j-1][0] + (s[j].x-s[i].x)*(c-s[i].d), d[i][j-1][1] + (s[j].x-s[j-1].x)*(c-s[i].d));
                c -= s[j].d;
            }
            dd -= s[i].d;
        }
        ans += min(d[0][n-1][0], d[0][n-1][1]);
    }
    cout << ans/v << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n>>v>>x && n) solve();
    return 0;
}