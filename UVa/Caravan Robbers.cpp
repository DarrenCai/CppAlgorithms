/**
 * UVa1616
 * 商队抢劫者
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 100010
#define M 1000010
struct seg {
    int a, b;
    bool operator< (const seg& rhs) const {
        return a < rhs.a;
    }
} a[N];

int n;
bool ok(int p, int q) {
    long long s = 0;
    for (int i=0; i<n; ++i) {
        long long t = a[i].a * (long long)q;
        long long r = (t > s ? t : s) + p;
        if (r > a[i].b * (long long)q) return false;
        s = r;
    }
    return true;
}

int gcd(int a, int b) {
    if (a > b) return gcd(b, a);
    if (a == 0) return b;
    if (a & 1) {
        if (b & 1) return gcd(a, (b-a)>>1);
        return gcd(a, b >> 1);
    } else {
        if (b & 1) return gcd(a >> 1, b);
        return gcd(a >> 1, b >> 1) << 1;
    } 
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) {
        int p, q = n, lp = n, s = M;
        for (int i=0; i<n; ++i) {
            cin >> a[i].a >> a[i].b;
            int l = a[i].b - a[i].a;
            if (l < s) s = l;
        }
        sort(a, a+n);
        p = a[0].b - a[0].a;
        for (int i=1; i<n; ++i) p += a[i].b - (a[i].a < a[i-1].b ? a[i-1].b : a[i].a);
        if (p / q >= s) p = s * q;
        if (!ok(p, q)) {
            while (lp <= p) {
                int mp = (p+lp) >> 1;
                if (ok(mp, q)) lp = mp + 1;
                else p = mp - 1;
            }
            for (int i=n-1; i>=1; --i) {
                int r = (long long)p * (q-i) % q;
                if (r>0 && r<i) {
                    s = (p+1)*(long long)i / q;
                    if (ok(s, i)) p = s, q = i;
                }
            }
        }
        s = gcd(q, p); p /= s; q /= s;
        cout << p << '/' << q << endl;
    }
    return 0;
}