/**
 * UVa11754
 * 数论难题
 */

#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

#define C 11
#define K 102
#define L 10000
int x[C], y[C][K], k[C], a[C], e[C], c, s, m, t; set<int> ans;

bool check(long long n) {
    for (int i=1; i<c; ++i) {
        int r = n % x[i], j = lower_bound(y[i], y[i]+k[i], r) - y[i];
        if (j==k[i] || y[i][j]>r) return false;
    }
    return true;
}

int gcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1; y = 0; return a;
    } else {
        int g = gcd(b, a%b, y, x);
        y -= a/b*x;
        return g;
    }
}

void dfs(int i = 0) {
    if (i == c) {
        long long x = 0; for (int i=0; i<c; ++i) x += (long long)e[i] * a[i];
        ans.insert((x%m + m) % m);
        return;
    }
    for (int j=0; j<k[i]; ++j) a[i] = y[i][j], dfs(i+1);
}

void solve() {
    long long l = 1;
    for (int i=0; i<c; ++i) {
        cin >> x[i] >> k[i];
        for (int j=0; j<k[i]; ++j) cin >> y[i][j];
        l *= k[i];
    }
    if (l > L) {
        for (int i=0; i<c; ++i) sort(y[i], y[i]+k[i]);
        for (long long i=0; s; ++i) for (int j=0; j<k[0]; ++j) {
            long long n = i*x[0] + y[0][j];
            if (n && check(n)) {
                cout << n << endl;
                if (--s == 0) return;
            }
        }
    } else {
        m = 1; for (int i=0; i<c; ++i) m *= x[i];
        for (int i=0; i<c; ++i) gcd(m/x[i], x[i], e[i], t), e[i] *= m/x[i];
        ans.clear(); dfs();
        for (long long i=0; s; ++i) for (set<int>::iterator it = ans.begin(); it != ans.end(); ++it) {
            long long n = i*m + *it;
            if (n > 0) {
                cout << n << endl;
                if (--s == 0) return;
            }
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>c>>s && c) solve(), cout << endl;
    return 0;
}