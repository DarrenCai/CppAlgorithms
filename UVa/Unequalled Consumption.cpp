/**
 * UVa12076/LA3408
 * 称糖果问题
 * Shanghai 2011
 */

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define X 8001
#define N 1<<14
#define D 50
int f[X], c[D], w[5], tot, n, g, m, d, kase = 0; long long a[D], b[D], t[D<<1];

struct complex {
    double x, y;
    void operator+= (const complex &t) {
        x += t.x; y += t.y;
    }
    complex operator- (const complex &t) const {
        return {x - t.x, y - t.y};
    }
    complex operator* (const complex &t) const {
        return {x * t.x - y * t.y, x * t.y + y * t.x};
    }
} s[5][N];

void fft(complex (&a)[N], int inv) {
    for (int i=0, j=0; i<tot; ++i) {
        if(j > i) {complex t = a[i]; a[i] = a[j]; a[j] = t;}
        int k = tot;
        while(j & (k >>= 1)) j &= ~k;
        j |= k;
    }
    for(int step=1; step<tot; step<<=1) {
        double alpha = inv*M_PI / step;
        for(int k=0; k<step; k++) {
            complex wk = {cos(alpha*k), sin(alpha*k)};
            for(int Ek=k; Ek<tot; Ek += step<<1) {
                int Ok = Ek + step; complex t = wk * a[Ok];
                a[Ok] = a[Ek] - t; a[Ek] += t;
            }
        }
    }
}

void solve1() {
    int q; cin >> q;
    while (q--) {
        long long p; cin >> p;
        p > 1 ? cout << "no candy for you" << endl : cout << w[0] << endl;
    }
}

void solve2() {
    int q, t = w[0]*w[1]/__gcd(w[0], w[1]), x = min(w[0], w[1]); cin >> q;
    while (q--) {
        long long p; cin >> p;
        cout << (p > 1 ? (p-1)*t : x) << endl;
    }
}

void mul(long long (&a)[D], const long long (&b)[D]) {
    int k = (d<<1) - 1;
    for (int i=0; i<k; ++i) t[i] = 0;
    for (int i=0; i<d; ++i) {
        if (a[i] == 0) continue;
        for (int j=0; j<d; ++j) t[i+j] += a[i] * b[j];
    }
    for (int i=k-1; i>=d; --i) {
        if (t[i] == 0) continue;
        for (int j=1; j<=d; ++j) t[i-j] -= t[i] * c[j];
    }
    for (int i=0; i<d; ++i) a[i] = t[i];
}

long long eval() {
    long long s = 0;
    for (int i=0; i<d; ++i) s += a[i]*f[i+1];
    return s;
}

long long kitamasa(int n) {
    for (int i=0; i<d; ++i) a[i] = i<1 ? 1 : 0, b[i] = i==1 ? 1 : 0;
    for (int x = n-1; x; x >>= 1) {
        if (x & 1) mul(a, b);
        mul(b, b);
    }
    return eval();
}

int query(long long p) {
    for (int i=1; i<X; ++i) if (f[i] >= p) return g*i;
    long x = pow(m*(double)p, 1./(n-1.)) - 70;
    long long s = kitamasa(x);
    for (int i=0; i<d; ++i) b[i] = i==1 ? 1 : 0;
    while (s < p) mul(a, b), s = eval(), ++x;
    return g*x;
}

void solve_n() {
    g = w[0]; m = 1; d = 0; tot = N;
    for (int i=1; i<n; ++i) g = __gcd(g, w[i]), m *=i;
    for (int i=0; i<n; ++i) w[i] /= g, m *= w[i], d += w[i];
    for (int i=0; i<X; ++i) f[i] = i%w[0] ? 0 : 1;
    for (int i=1; i<n; ++i) {
        for (int j=0; j<tot; ++j) s[0][j] = {j>=X ? 0. : 1.*f[j], 0.}, s[i][j] = {j>=X || j%w[i] ? 0. : 1., 0.};
        fft(s[0], 1); fft(s[i], 1);
        for (int j=0; j<tot; ++j) s[0][j] = s[0][j] * s[i][j];
        fft(s[0], -1);
        for (int j=0; j<X; ++j) f[j] = s[0][j].x / tot + .5;
    }
    for (tot=1; tot <= d; tot <<= 1);
    for (int i=0; i<=d; ++i) c[i] = i<1 ? 1 : (i==w[0] ? -1 : 0);
    for (int i=1; i<n; ++i) {
        for (int j=0; j<tot; ++j) s[0][j] = {j>d ? 0. : 1.*c[j], 0.}, s[i][j] = {j<1 ? 1. : (j==w[i] ? -1. : 0.), 0.};
        fft(s[0], 1); fft(s[i], 1);
        for (int j=0; j<tot; ++j) s[0][j] = s[0][j] * s[i][j];
        fft(s[0], -1);
        for (int j=0; j<=d; ++j) c[j] = s[0][j].x / tot + (s[0][j].x > 0. ? .5 : -.5);
    }
    int q; cin >> q;
    while (q--) {
        long long p; cin >> p;
        cout << query(p) << endl;
    }
}

void solve() {
    for (int i=0; i<n; ++i) cin >> w[i];
    cout << "Set "<< ++kase << endl;
    if (n == 1) solve1();
    else if (n == 2) solve2();
    else solve_n();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) solve();
    return 0;
}