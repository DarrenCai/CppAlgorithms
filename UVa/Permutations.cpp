/**
 * UVa11303
 * 排列
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 255

struct integer {
    int a[56], n;
    integer():n(0){}
    integer(const char* s) {
        int m = strlen(s); n = 0; long long v = 0, p=1;
        for (int i=m-1; i>=0; --i) {
            v = p*(s[i] - '0') + v;
            p*=10;
            if (v >= 1000000000 || p==1000000000) {
                a[n++] = v%1000000000;
                v /= 1000000000;
                p = v >= 1000000000 ? 10 : 1;
            }
        }
        if (v > 0) a[n++] = v;
    }
    bool operator< (const integer& x) const {
        if (n == x.n) {
            for (int i=n-1; i>=0; --i) if (a[i] != x.a[i]) return a[i] < x.a[i];
            return false;
        }
        return n < x.n;
    }
    bool operator== (const integer& x) const {
        if (n != x.n) return false;
        for (int i=0; i<n; ++i) if (a[i] != x.a[i]) return false;
        return true;
    }
    integer operator+ (const integer& x) const {
        int m = max(n, x.n); long long r = 0; integer y;
        for (int i=0; i<m; ++i) {
            r = r + (i < n ? a[i] : 0) + (i < x.n ? x.a[i] : 0);
            y.a[y.n++] = r%1000000000;
            r /= 1000000000;
        }
        if (r > 0) y.a[y.n++] = r;
        return y;
    }
    integer operator- (const integer& x) const {
        integer y = *this;
        for (int i=0; i<y.n; ++i) {
            y.a[i] -= i < x.n ? x.a[i] : 0;
            if (y.a[i] < 0) {
                --y.a[i+1];
                y.a[i] += 1000000000;
            }
        }
        if (y.a[y.n-1] == 0) --y.n;
        return y;
    }
    integer operator* (const long long& x) const {
        integer y = *this;
        if (x == 0) {
            y.n = 0;
            return y;
        }
        long long r = 0;
        for (int i=0; i<y.n; ++i) {
            r = r + y.a[i]*x;
            y.a[i] = r%1000000000;
            r /= 1000000000;
        }
        if (r > 0) y.a[y.n++] = r;
        return y;
    }
    int operator/ (const integer& x) const {
        if (*this < x) return 0;
        __uint128_t y = x.a[x.n-1], z = n>x.n ? a[n-1]*(__uint128_t)1000000000 + a[n-2] : a[n-1];
        if (y<10000 && x.n>1) {
            y = y*1000000000 + x.a[x.n-2];
            z = z*1000000000 + a[x.n-2];
        }
        int k = z/y; integer i = x * k;
        if (i == *this) return k;
        if (*this < i) return --k;
        i = x + i;
        if (!(*this<i)) ++k;
        return k;
    }
} d[N][N];

char s[505]; bool f[251]; int a[251], b[251], n, m, t;

void erase(int i) {
    --t;
    for (int j=i; j<t; ++j) b[j] = b[j+1];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int m=0; m<N; ++m) {
        d[m][m].a[0] = 1; d[m][m].n = 1;
        for (int n=m+1; n<N; ++n) d[m][n] = d[m][n-1]*n;
    }
    while (cin >> n >> m >> s) {
        integer k(s);
        memset(f, t = 0, sizeof(f));
        for (int i=0; i<m; ++i) cin >> a[i], f[a[i]] = true;
        if (m == n) {
            for (int i=1; i<m; ++i) cout << a[i-1] << ' ';
            cout << a[m-1] << endl;
            continue;
        }
        for (int i=1; i<=n; ++i) if (!f[i]) b[t++] = i;
        for (int i=1; i<n; ++i) {
            int p = m+t+i-n-1;
            if (p == m) {
                int x = k/d[0][n-i];
                if (x > 0) {
                    k = k-(d[0][n-i]*(d[0][n-i]*x == k ? --x : x));
                    cout << b[x] << ' ';
                    erase(x);
                } else {
                    cout << b[0] << ' ';
                    erase(0);
                }
            } else {
                int j = min(lower_bound(b, b+t, a[p]-1) - b, long(t-1));
                if (b[j] > a[p]) --j;
                int x = k/d[m-p][n-i], y = min(j, x);
                integer k1 = d[m-p][n-i]*(y+1);
                if (k < k1) {
                    integer k2 = d[m-p][n-i]*y;
                    if (k == k2) {
                        cout << b[--y] << ' ';
                        erase(y);
                        while (++i < n) cout << (t==0 ? a[p++] : (p==m || (b[t-1] > a[p]) ? b[--t] : a[p++])) << ' ';
                        break;
                    }
                    cout << b[y] << ' ';
                    erase(y);
                    k = k-k2;
                } else if (k1 == k) {
                    cout << b[y] << ' ';
                    erase(y);
                    while (++i < n) cout << (t==0 ? a[p++] : (p==m || (b[t-1] > a[p]) ? b[--t] : a[p++])) << ' ';
                    break;
                } else {
                    integer k2 = k1 + d[m-p-1][n-i];
                    if (k < k2) {
                        cout << a[p] << ' ';
                        k = k-k1;
                    } else if (k == k2) {
                        cout << a[p++] << ' ';
                        while (++i < n) cout << (t==0 ? a[p++] : (p==m || (b[t-1] > a[p]) ? b[--t] : a[p++])) << ' ';
                        break;
                    } else {
                        k1 = k - k2;
                        x = k1/d[m-p][n-i];
                        if (d[m-p][n-i]*x == k1) {
                            cout << b[y+=x] << ' ';
                            erase(y);
                            while (++i < n) cout << (t==0 ? a[p++] : (p==m || (b[t-1] > a[p]) ? b[--t] : a[p++])) << ' ';
                            break;
                        } else {
                            y = y + x;
                            k2 = d[m-p][n-i]*x;
                            if (k2 < k1) ++y;
                            cout << b[y] << ' ';
                            erase(y);
                            if (k2 == k1) {
                                while (++i < n) cout << (t==0 ? a[p++] : (p==m || (b[t-1] > a[p]) ? b[--t] : a[p++])) << ' ';
                                break;
                            }
                            k = k1-k2;
                        }
                    }
                }
            }
            // cout << flush;
        }
        cout << (t==0 ? a[m-1] : b[0]) << endl;
    }
    return 0;
}