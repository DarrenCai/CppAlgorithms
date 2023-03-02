/**
 * UVa1126/LA2683
 * 支付系统
 * SEERC 2006
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define M 334
char s[105]; int len; bool eq; long long base = 100000000000000000ll;

struct intg {
    long long a[6]; int n;
    intg():n(1) {a[0] = 1;}
    void from_s() {
        n = (len+16) / 17;
        for (int i=n-1, l=0, r=len%17 ? len%17 : 17; i>=0; --i, l=r, r+=17) {
            a[i] = 0;
            for (int j=l; j<r; ++j) a[i] = 10*a[i] + s[j]-'0';
        }
    }
    void double_v(const intg& x) {
        long long r = 0; n = x.n;
        for (int i=0; i<n; ++i) r += 2*x.a[i], a[i] = r%base, r /= base;
        if (r) a[n++] = r;
    }
    bool operator< (const intg& x) const {
        if (n != x.n) return n < x.n;
        for (int i=n-1; i>=0; --i) if (a[i] != x.a[i]) return a[i] < x.a[i];
        return false;
    }
} a[334], v;

int nth_root(int x, int n) {
    int l = 2, r = 9; eq = false;
    while (l <= r) {
        int m = (l+r)>>1, y = m;
        for (int i=1; i<n; ++i) y *= m;
        if (y == x) {
            eq = true;
            return m;
        }
        y<x ? l = m+1 : r = m-1;
    }
    return r;
}

bool solve_small() {
    if ((len = strlen(s)) > 2) return false;
    int x = s[0]-'0';
    if (s[1]) x = 10*x + s[1]-'0';
    if (x > 63) return false;
    for (int i=5; i>1; --i) {
        int r = nth_root(x, i);
        if (eq) {
            if (i != 4) cout << r << '^' << i << endl;
            else cout << r << "^2^2" << endl;
            return true;
        }
    }
    cout << x << endl;
    return true;
}

void exponents(int n) {
    if (n < 4) cout << n << endl;
    else if (n == 4) cout << "^2^2" << endl;
    else if (n == 5) cout << "^5" << endl;
    else if (n < 8) cout << "^3^2" << endl;
    else if (n == 8) cout << "^2^2^2" << endl;
    else if (n == 9) cout << "^3^3" << endl;
    else cout << "^2", exponents(n >> 1);
}

void solve() {
    if (solve_small()) return;
    v.from_s();
    cout << 2;
    exponents(upper_bound(a, a+M, v) - a - 1);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=1; i<M; ++i) a[i].double_v(a[i-1]);
    while (cin >> s) solve();
    return 0;
}