
/**
 * UVa1377
 * 刻度尺
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 300
#define M 7
int d[N], s[N], a[M]; short c[N], n, m, t;

bool dfs(short p = 0, short k = 1, short cc = 1) {
    if (k == m-1) return cc == n; 
    if (t-p < m-k-1 || m*(m-1)/2 - k*(k+1)/2 + cc < n) return false;
    for (short i=p; i<t; ++i) {
        a[k] = s[i];
        int v = a[m-1] - a[k]; bool f = false;
        short ii = lower_bound(d, d+n, v) - d;
        if (ii<n && d[ii]==v && !c[ii]++) f = ++cc;
        for (short j=0; j<k; ++j) {
            v = a[k] - a[j]; ii = lower_bound(d, d+n, v) - d;
            if (ii<n && d[ii]==v && !c[ii]++) f = ++cc;
        }
        if (f && dfs(i+1, k+1, cc)) return true;
        v = a[m-1] - a[k]; ii = lower_bound(d, d+n, v) - d;
        if (ii<n && d[ii]==v && !--c[ii]) --cc;
        for (short j=0; j<k; ++j) {
            v = a[k] - a[j]; ii = lower_bound(d, d+n, v) - d;
            if (ii<n && d[ii]==v && !--c[ii]) --cc;
        }
    }
    return false;
}

short solve() {
    for (short i=0; i<n; ++i) cin >> d[i];
    sort(d, d+n);
    n = unique(d, d+n) - d;
    if (n == 1) {
        a[1] = d[0];
        return m = 2;
    }
    if (n > M*(M-1)/2) return m = 0;
    t = n*(n+1)/2;
    for (short i=0, k=0; i<n; ++i) {
        c[i] = 0; s[k++] = d[i];
        for (short j=i+1; j<n; ++j) s[k++] = d[j]-d[i];
    }
    sort(s, s+t);
    t = unique(s, s+t) - s - 1;
    c[n-1] = 1;
    for (m=2; m<=M; ++m) if (m*(m-1)/2 >= n) {
        a[m-1] = s[t];
        if (dfs()) return m;
    }
    return m = 0;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int kase = a[0] = 0;
    while (cin>>n && n) {
        cout << "Case " << ++kase << ':' << endl;
        solve();
        if (m) {
            cout << m << endl << 0;
            for (short i=1; i<m; ++i) cout << ' ' << a[i];
            cout << endl;
        } else cout << 0 << endl << endl;
    }
    return 0;
}
