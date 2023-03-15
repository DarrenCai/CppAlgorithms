/**
 * UVa1503/LA5769
 * 鸡兔同笼问题扩展
 * Chengdu 2011
 */

#include <iostream>
using namespace std;

#define N 1002
int a[N], l[N], c[N], n, k;

int gcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1; y = 0; return a;
    } else {
        int g = gcd(b, a%b, y, x);
        y -= a/b*x;
        return g;
    }
}

int dfs(int kk = 0, int cc = 0) {
    if (a[kk] < 0) return 0;
    if (kk == 0) {
        if (a[0] < a[1]) return 0;
        l[cc = 1] = 1; c[1] = a[0] - a[1];
        return dfs(1, cc);
    }
    if (kk == k) {
        if (cc == n) {
            if (a[k] % c[n]) return 0;
            l[n] += a[k]/c[n];
            return 1;
        }
        int p = cc, t = n-cc+1, x = (l[cc]-k)*c[cc] + (t-1)*t/2;
        if (c[p] < t || a[k] < x) return 0;
        c[p+1] = t-1; l[p+1] = l[p] +1;
        while (++cc < n) c[cc+1] = c[cc]-1, l[cc+1] = l[cc]+1;
        l[n] += a[k]-x;
        if (a[k] == x) return 1;
        if (a[k] == x+1) return c[p] == t ? 1 : 2;
        if (t > 2) return 2;
        int cnt = 0;
        for (int i=1; i<c[p]; ++i) {
            int x, y, g = gcd(i, c[p]-i, x, y);
            if (a[k] % g) continue;
            x *= a[k]/g; y *= a[k]/g;
            int a = i/g, b = (c[p]-i)/g;
            if (x < 0) {
                int k = (b-1-x) / b;
                x += b*k; y -= a*k;
            }
            if (y>x && (++cnt > 1 || x+b < y-a)) return 2;
        }
        return 1;
    }
    if (a[kk-1] < a[kk] || a[kk] - a[kk+1] > a[kk-1] - a[kk]) return 0;
    if (a[kk] - a[kk+1] < a[kk-1] - a[kk]) {
        if (a[kk] == a[kk+1]) {
            if (a[kk]) return 0;
            return dfs(kk+1, cc);
        }
        l[cc+1] = l[cc]+1;
        if (++cc > n) return 0;
        c[cc] = a[kk] - a[kk+1];
    } else ++l[cc];
    return dfs(kk+1, cc);
}

void solve() {
    cin >> n >> k;
    for (int i=0; i<=k; ++i) cin >> a[i];
    while (k>0 && a[k]==0 && a[k-1] == 0) --k;
    int x = dfs();
    if (x > 1) cout << "Multiple Solutions" << endl;
    else if (x > 0) {
        cout << "Unique Solution" << endl;
        for (int i=1; i<=n; ++i) cout << l[i] << " " << (i<n ? c[i]-c[i+1] : c[i]) << endl;
    } else cout << "No Solution" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) {
        cout << "Case #" << k << ':' << endl;
        solve();
    }
    return 0;
}