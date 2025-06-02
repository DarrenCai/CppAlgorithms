/**
 * UVa1457/LA4746
 * 信息解密
 * Shanghai 2009
 * 解高次模方程，涉及原根、离散对数等知识，参见https://oi-wiki.org/math/number-theory/discrete-logarithm/
 */

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <vector>
#include <map>
using namespace std;

#define T 32
int c[T] = {0}, p, q, a, t, kase = 0;

int gcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1; y = 0; return a;
    } else {
        int g = gcd(b, a%b, y, x);
        y -= a/b*x;
        return g;
    }
}

int inv(int a, int n) {
    int x, y;
    return gcd(a, n, x, y) == 1 ? (x + n) % n : -1;
}

int pow_mod(long long a, int n) {
    int ans = 1;
    while (n) {
        if (n & 1) ans = ans*a % p;
        a = a*a % p; n >>= 1;
    }
    return ans;
}

bool is_primitive_root(int m) {
    for (int i=2; i*i<p; ++i) if ((p-1) % i == 0 && (pow_mod(m, i) == 1 || pow_mod(m, (p-1)/i) == 1)) return false;
    return true;
}

int bsgs(int a, int b) {
    int m = sqrt(p+.5), s = inv(pow_mod(a, m), p), e = 1; map<int, int> x;
    x[1] = 0;
    for (int i=1; i<m; ++i) {
        e = e*(long long)a % p;
        if (!x.count(e)) x[e] = i;
    }
    for (int i=0, j=(p+m-1)/m; i<j; ++i) {
        if (x.count(b)) return i*m + x[b];
        b = b*(long long)s %p;
    }
    return -1;
}

int f(int x) {
    return (x%4 == 0 && (x%100 || x%400 == 0) ? 31622400 : 31536000) + (x%10 == 5 || x%10 == 8);
}

void print(int x) {
    int y = T-1, m = 12, d, hh, mm, ss;
    for (int i=1; i<T; ++i) if (c[i] >= x) {
        y = c[i] == x ? i : i-1;
        break;
    }
    if ((x -= c[y]) == 0) {
        cout << y+2000 << ".01.01 00:00:00" << endl;
    } else {
        bool f = y%4 == 0 && (y%100 || y%400 == 0);
        for (int i=1, t=0; i<13; ++i) {
            int s = (i==2 ? 28+f : (i==4 || i==6 || i==9 || i==11 ? 30 : 31)) * 86400;
            if (i==12 || t+s > x) {
                m = i; x -= t;
                break;
            }
            t += s;
        }
        d = min((x + 86399) / 86400, 31); x -= 86400*(d-1);
        hh = min(x / 3600, 23); x -= 3600*hh;
        mm = min(x / 60, 59); ss = x - 60*mm;
        cout << y+2000 << '.' << setw(2) << m << '.' << setw(2) << d << ' '
            << setw(2) << hh << ':' << setw(2) << mm << ':' << setw(2) << ss << endl;
    }
}

void solve() {
    cin >> p >> q >> a;
    cout << "Case #" << ++kase << ':' << endl;
    if (a == 0) {
        cout << "2000.01.01 00:00:00" << endl;
        return;
    }
    int m, x, y;
    for (m=2; m<p; ++m) if (is_primitive_root(m)) break;
    int b = bsgs(m, a), g = gcd(q, p-1, x, y);
    if (b % g) {
        cout << "Transmission error" << endl;
        return;
    }
    vector<int> ans; x = (x*(long long)b/g % (p-1) + p-1) % (p-1); y = (p-1) / g;
    for (int i=0; i<g; ++i) ans.push_back(pow_mod(m, x+i*y));
    sort(ans.begin(), ans.end());
    g = unique(ans.begin(), ans.end()) - ans.begin();
    for (int i=0; i<g; ++i) print(ans[i]);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=1; i<T; ++i) c[i] = c[i-1] + f(i-1);
    cin >> t; cout << setfill('0');
    while (t--) solve();
    return 0;
}