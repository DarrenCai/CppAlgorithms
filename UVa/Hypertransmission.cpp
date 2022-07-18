/**
 * UVa1325/LA2963
 * 超级传输
 * Regionals 2003 >> Europe - Northeastern
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;

#define N 1030
int x[N], y[N], z[N], p[N], f[N], n, t;
struct node {
    int a, b, d;
    bool operator< (const node& rhs) const {
        return d < rhs.d;
    }
} s[N*N>>1];

void solve() {
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i] >> z[i] >> p[i], f[i] = 1;
    for (int i=t=0; i<n; ++i) for (int j=i+1; j<n; ++j) {
        s[t].d = (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]) + (z[i]-z[j])*(z[i]-z[j]);
        s[t].a = i; s[t++].b = j;
    }
    sort(s, s+t);
    int c = 0, cc = 0, r = 0;
    for (int i=0; i<t; ++i) {
        int a = s[i].a, b = s[i].b, d = s[i].d;
        if (p[a] == p[b]) {
            if (++f[a] == 0) --cc;
            if (++f[b] == 0) --cc;
        } else {
            if (f[a]-- == 0) ++cc;
            if (f[b]-- == 0) ++cc;
        }
        if (i+1<t && d==s[i+1].d) continue;
        if (cc > c) c = cc, r = d;
    }
    cout << c << endl;
    cout << sqrt(r) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(4);
    while (cin >> n) solve();
    return 0;
}