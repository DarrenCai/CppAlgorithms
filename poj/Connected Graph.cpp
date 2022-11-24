/**
 * poj1737
 * oeis出处：https://oeis.org/A001187
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define R 1000000000
#define M 137
#define N 51
struct num {
    int v[M], n;
    void operator= (int x) {
        v[0] = x; n =1;
    }
    void operator<<= (int x) {
        int r = 0;
        for (int i=0; i<n; ++i) v[i] = (v[i]<<1) + r, r = v[i] >= R, v[i] %= R;
        if (r) v[n++] = 1;
        while (--x) *this <<= 1;
    }
    void operator+= (const num& x) {
        int r = 0;
        for (int i=0; i<n; ++i)
            v[i] += (i<x.n ? x.v[i] : 0) + r, r = v[i] >= R, v[i] %= R;
        while (n < x.n)
            v[n] = x.v[n] + r, r = v[n] >= R, v[n++] %= R;
        if (r) v[n++] = 1;
    }
    void print() const {
        cout << v[n-1];
        for (int i=n-2; i>=0; --i) cout << setw(9) << v[i];
        cout << endl;
    }
} c[N][N], f[N], g[N], h[N];

num operator+ (const num& x, const num& y) {
    num z; z.n = y.n; int r = 0;
    for (int i=0; i<y.n; ++i)
        z.v[i] = (i<x.n ? x.v[i] : 0) + y.v[i] + r, r = z.v[i] >= R, z.v[i] %= R;
    while (z.n < x.n)
        z.v[z.n] = x.v[z.n] + r, r = z.v[z.n] >= R, z.v[z.n++] %= R;
    if (r) z.v[z.n++] = 1;
    return z;
}

num operator- (const num& x, const num& y) {
    num z; z.n = x.n; int r = 0;
    for (int i=0; i<x.n; ++i) {
        int a = x.v[i] - (r ? 1 : 0), b = i<y.n ? y.v[i] : 0;
        r = a < b ? R : 0; z.v[i] = a + r - b;
    }
    if (z.v[z.n-1] == 0) --z.n;
    return z;
}

num operator* (const num& x, const num& y) {
    num z; z.n = x.n + y.n - 1;
    for (int i=0; i<=z.n; ++i) z.v[i] = 0;
    for (int i=0; i<x.n; ++i) for (int j=0, k; j<y.n; ++j) {
        long long v = x.v[i]; v *= y.v[j];
        z.v[k = i+j] += v % R;
        if (z.v[k] >= R) ++z.v[k+1], z.v[k] %= R;
        z.v[k+1] += v / R;
        if (z.v[k+1] >= R) ++z.v[k+2], z.v[k+1] %= R;
    }
    if (z.v[z.n]) ++z.n;
    return z;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    c[0][0] = 1; c[1][0] = 1; c[1][1] = 1; f[1] = 1; g[1] = 0; h[1] = 1;
    for (int i=2; i<N; ++i) {
        c[i][0] = 1; c[i][i] = 1; g[i] = 0; h[i] = h[i-1]; h[i] <<= i-1;
        for (int j=(i+1)>>1; j>0; --j) c[i][j] = c[i][i-j] = c[i-1][j-1] + c[i-1][j];
        for (int k=1; k<i; ++k) g[i] += c[i-1][k-1]*f[k]*h[i-k];
        f[i] = h[i] - g[i];
    }
    cout << setfill('0');
    int n;
    while (cin>>n && n) f[n].print();
    return 0;
}