/**
 * UVa1426/LA4270
 * 离散平方根
 */

#include <iostream>
#include <set>
using namespace std;

int x, y, n, r, kase = 0;

int gcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1; y = 0; return a;
    } else {
        int g = gcd(b, a%b, y, x);
        y -= a/b*x;
        return g;
    }
}

void solve() {
    long long c = 2ll*r; set<int> ans;
    for (int a=1; a*a<=n; ++a) if (n%a == 0) {
        int g = gcd(a, n/a, x, y);
        if (c % g) continue;
        long long cc = c/g*a*x - r, b = n/g;
        for (long long k = (cc<0 ? -cc+b-1 : -cc)/b; k*b+cc<n; ++k) ans.insert(k*b+cc);
        if (a*a == n) continue;
        gcd(n/a, a, x, y);
        cc = c/g*n/a*x - r;
        for (long long k = (cc<0 ? -cc+b-1 : -cc)/b; k*b+cc<n; ++k) ans.insert(k*b+cc);
    }
    cout << "Case " << ++kase << ':';
    for (set<int>::iterator it=ans.begin(); it!=ans.end(); ++it) cout << ' ' << *it;
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>x>>n>>r && n) solve();
    return 0;
}