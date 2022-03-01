/**
 * UVa11134
 * 传说中的车
 */

#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

#define N 5010
short xl[N], xr[N], yl[N], yr[N], ax[N], ay[N], x[N], y[N], n;

bool cmpxl(short i, short j) {
    return xl[i] < xl[j] || (xl[i]==xl[j] && i<j);
}

bool cmpyl(short i, short j) {
    return yl[i] < yl[j] || (yl[i]==yl[j] && i<j);
}

struct cmpxr {
    bool operator() (short i, short j) const {
        return xr[i] < xr[j] || (xr[i]==xr[j] && i<j);
    }
};

struct cmpyr {
    bool operator() (short i, short j) const {
        return yr[i] < yr[j] || (yr[i]==yr[j] && i<j);
    }
};

bool check() {
    sort(x, x+n, cmpxl);
    set<short, cmpxr> s; short c = 0;
    for (short i=1; i<=n; ++i) {
        while (c<n && xl[x[c]]<=i) s.insert(x[c++]);
        if (s.empty() || xr[*s.begin()]<i) return false;
        ax[*s.begin()] = i; s.erase(s.begin());
    }
    sort(y, y+n, cmpyl);
    set<short, cmpyr> q; c = 0;
    for (short i=1; i<=n; ++i) {
        while (c<n && yl[y[c]]<=i) q.insert(y[c++]);
        if (q.empty() || yr[*q.begin()]<i) return false;
        ay[*q.begin()] = i; q.erase(q.begin());
    }
    return true;
}

void solve() {
    for (short i=0; i<n; ++i) cin >> xl[i] >> yl[i] >> xr[i] >> yr[i], x[i] = y[i] = i;
    if (check()) {
        for (short i=0; i<n; ++i) cout << ax[i] << ' ' << ay[i] << endl;
    } else cout << "IMPOSSIBLE" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n && n) solve();
    return 0;
}