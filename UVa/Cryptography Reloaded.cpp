/**
 * UVa1431/LA4353
 * 密码学问题
 * Hangzhou 2008
 */

#include <iostream>
#include <iomanip>
using namespace std;

int e, kase = 0; char s[105];
const long long base = 100000000000000000ll;
struct intg {
    long long a[13]; int n;
    bool read() {
        cin >> s;
        if (s[0] == '0') return false;
        int t = 0; while (s[t]) ++t;
        n = (t+16) / 17;
        for (int i=n-1, l=0, r=t%17 ? t%17 : 17; i>=0; --i, l=r, r+=17) {
            a[i] = 0;
            for (int j=l; j<r; ++j) a[i] = 10*a[i] + s[j]-'0';
        }
        return true;
    }
    void write() {
        cout << a[n-1];
        for (int i=n-2; i>=0; --i) cout << setw(17) << setfill('0') << a[i];
    }
    void operator*= (int x) {
        __int128_t r = 0, y = x;
        for (int i=0; i<n; ++i) r += y*a[i], a[i] = r%base, r /= base;
        if (r > 0) a[n++] = r;
    }
    void operator*= (const intg& x) {
        intg y = *this; n = x.n+y.n-1; __int128_t r = 0;
        for (int i=0; i<n; ++i) {
            __int128_t v = r % base; r /= base;
            for (int j=min(i, x.n-1); j>=0; --j) {
                int k = i-j;
                if (k >= y.n) break;
                v += x.a[j] * __int128_t(y.a[k]);
                if (v >= base) r += v/base, v %= base;
            }
            a[i] = v;
        }
        if (r > 0) a[n++] = r;
    }
    void operator-= (int x) {
        a[0] -= x;
        for (int i=0; i<n; ++i) {
            if (a[i] >= 0) break;
            a[i] += base; --a[i+1];
        }
        if (n>1 && a[n-1]==0) --n;
    }
    void operator-= (const intg& x) {
        for (int i=0; i<n; ++i) {
            if (i < x.n) a[i] -= x.a[i];
            if (a[i] >= 0) continue;
            a[i] += base; --a[i+1];
        }
        while (n>1 && a[n-1]==0) --n;
    }
    void operator+= (int x) {
        a[0] += x;
        for (int i=0; i<n; ++i) {
            if (a[i] < base) break;
            a[i] = 0; ++a[i+1];
            if (i+1 == n) a[n++] = 1;
        }
    }
    void operator+= (const intg& x) {
        int m = max(n, x.n), r = 0;
        for (int i=0; i<m; ++i) {
            long long v = (i<n ? a[i] : 0) + (i<x.n ? x.a[i] : 0) + r;
            a[i] = v % base; r = v / base;
        }
        n = m;
        if (r > 0) a[n++] = r;
    }
    int operator% (int x) {
        int r = 0; __int128_t b = base;
        for (int i=n-1; i>=0; --i) r = (r*b + a[i]) % x;
        return r;
    }
    void operator/= (int x) {
        __int128_t r = 0;
        for (int i=n-1; i>=0; --i) r = r*base + a[i], a[i] = r/x, r %= x;
        if (n>1 && a[n-1]==0) --n;
    }
    bool operator< (const intg& x) {
        if (n != x.n) return n < x.n;
        for (int i=n-1; i>=0; --i) if (a[i] != x.a[i]) return a[i] < x.a[i];
        return false;
    }
    bool operator<= (const intg& x) {
        if (n != x.n) return n < x.n;
        for (int i=n-1; i>=0; --i) if (a[i] != x.a[i]) return a[i] < x.a[i];
        return true;
    }
    bool operator== (const intg& x) {
        if (n != x.n) return false;
        for (int i=0; i<n; ++i) if (a[i] != x.a[i]) return false;
        return true;
    }
} n, d, p, q, r;

bool sqrt(const intg& x) {
    intg l, mid, v; l.n = 1; l.a[0] = 1;
    r.n = (x.n+1)>>1; for (int i=r.n-1; i>=0; --i) r.a[i] = base-1;
    while (l <= r) {
        mid = l; mid += r; mid /= 2; v = mid; v *= mid;
        if (v == x) {
            r = mid; return true;
        } 
        v < x ? (l = mid, l += 1) : (r = mid, r -= 1);
    }
    return false;
}

void solve() {
    d.read(); cin >> e;
    intg c = n, de = d, b, t; c *= 4; de *= e; de -= 1;
    for (int i=1; i<e; ++i) if (de%i == 0) {
        t = de; t /= i; t -= 1;
        if (n <= t) continue;
        b = n; b -= t; t = b; t *= b;
        if (t <= c) continue;
        t -= c;
        if (sqrt(t)) {
            p = b; p -= r; p /= 2; q = b; q += r; q /= 2;
            cout << "Case #" << ++kase << ": ";
            p.write(); cout << ' '; q.write(); cout << endl;
            return;
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while(n.read()) solve();
    return 0;
}