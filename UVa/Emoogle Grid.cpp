/**
 * UVa11916
 * 网格涂色
 */

#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define M 100000007
#define B 1000100
#define S 10001
struct grid {
    int r, c;
    bool operator< (const grid& rhs) const {
        return c<rhs.c || (c==rhs.c && r<rhs.r);
    }
} a[B];
int n, k, b, t; long long r;

long long pow(int x, long long n) {
    if (n == 0) return 1;
    long long r = pow(x, n>>1) % M;
    r = r*r % M;
    return n&1 ? r*x % M : r;
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

int log(int a, int b) {
    long long r = b, t = pow(a, S); map<int, int> mp;
    for (int i=0; i<=S; ++i, r=r*a%M) mp[r] = i;
    r = t;
    for (int i=1; i<=S; ++i, r = r*t%M) if (mp.count(r)) return i*S - mp[r];
    return -1;
}

int solve() {
    long long c = 0; int m = 1, d = 0;
    cin >> n >> k >> b >> r;
    for (int i=0; i<b; ++i) cin >> a[i].r >> a[i].c, m = max(a[i].r, m);
    sort(a, a+b);
    int x = m, y = 0;
    for (int i=0; i<b; ++i) {
        if (a[i].c != y) c += a[i].c-y - (x==m);
        if (a[i].r>1 && (a[i].c!=y || (a[i].c==y && a[i].r>x+1))) ++c;
        x = a[i].r; y = a[i].c;
        if (x == m) ++d;
    }
    c += n+1-y - (x==m);
    long long t = (long long)m*n - b;
    t = pow(k, c) * pow(k-1, t-c) % M;
    if (t == r) return m;
    ++m;
    t = t * pow(k, d) % M * pow(k-1, n-d) % M;
    if (t == r) return m;
    gcd(t, M, x, y);
    return log(pow(k-1, n), (x + M) % M * r % M) + m;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Case " << kase << ": " << solve() << endl;
    return 0;
}