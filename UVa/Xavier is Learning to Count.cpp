/**
 * UVa12327/LA5705
 * 学习数数的Xavier
 * Shanghai 2011
 */

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

#define M 13001
#define N 1<<16

bool f[M]; int tot, x, kase = 0;

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
} s1[N], s2[N], s3[N], s4[N], s5[N], s6[N], s7[N];

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
    for (int i=1; i<=x; ++i) if (f[i]) cout << i << ": " << 1 << endl;
}

void solve2() {
    fft(s2, -1);
    for (int i=0; i<tot; ++i) {
        long long a = s2[i].x / tot + .5;
        if (~i&1 && (i>>1)<=x && f[i>>1]) --a;
        if (a) cout << i << ": " << a/2 << endl;
    }
}

void solve3() {
    for (int i=0; i<tot; ++i) s3[i] = s2[i] * s1[i];
    for (int i=0; i<tot; ++i) s2[i] = {~i&1 && (i>>1)<=x && f[i>>1] ? 1. : 0., 0.};
    fft(s2, 1);
    for (int i=0; i<tot; ++i) s2[i] = s2[i] * s1[i];
    fft(s2, -1); fft(s3, -1);
    for (int i=0; i<tot; ++i) {
        long long a = s3[i].x / tot + .5, b = s2[i].x / tot + .5;
        if (i%3==0 && i/3<=x && f[i/3]) --a, --b;
        a -= 3*b;
        if (a) cout << i << ": " << a/6 << endl;
    }
}

void solve4() {
    for (int i=0; i<tot; ++i) s4[i] = s2[i] * s2[i];
    for (int i=0; i<tot; ++i) s3[i] = {i%3==0 && i/3<=x && f[i/3] ? 1. : 0., 0.};
    for (int i=0; i<tot; ++i) s5[i] = {~i&1 && (i>>1)<=x && f[i>>1] ? 1. : 0., 0.};
    fft(s3, 1); fft(s5, 1);
    for (int i=0; i<tot; ++i) s3[i] = s3[i] * s1[i];
    for (int i=0; i<tot; ++i) s2[i] = s5[i] * s2[i];
    for (int i=0; i<tot; ++i) s5[i] = s5[i] * s5[i];
    fft(s2, -1); fft(s3, -1); fft(s4, -1); fft(s5, -1);
    for (int i=0; i<tot; ++i) {
        long long a = s4[i].x / tot + .5, b = s3[i].x / tot + .5, c = s2[i].x / tot + .5, d = s5[i].x / tot + .5;
        if ((i&3)==0 && (i>>2)<=x && f[i>>2]) --a, --b, --c, --d;
        a -= 6*c - 8*b - 3*d;
        if (a) cout << i << ": " << a/24 << endl;
    }
}

void solve5() {
    for (int i=0; i<tot; ++i) s4[i] = {(i&3)==0 && (i>>2)<=x && f[i>>2] ? 1. : 0., 0.};
    for (int i=0; i<tot; ++i) s3[i] = {i%3==0 && i/3<=x && f[i/3] ? 1. : 0., 0.};
    fft(s4, 1); fft(s3, 1);
    for (int i=0; i<tot; ++i) s6[i] = s3[i];
    for (int i=0; i<tot; ++i) s5[i] = s2[i] * s2[i] * s1[i];
    for (int i=0; i<tot; ++i) s4[i] = s4[i] * s1[i];
    for (int i=0; i<tot; ++i) s3[i] = s3[i] * s2[i];
    for (int i=0; i<tot; ++i) s2[i] = {~i&1 && (i>>1)<=x && f[i>>1] ? 1. : 0., 0.};
    fft(s2, 1);
    for (int i=0; i<tot; ++i) s7[i] = s2[i] * s2[i] * s1[i];
    for (int i=0; i<tot; ++i) s6[i] = s6[i] * s2[i];
    for (int i=0; i<tot; ++i) s2[i] = s2[i] * s1[i] * s1[i] * s1[i];
    fft(s2, -1); fft(s3, -1); fft(s4, -1); fft(s5, -1); fft(s6, -1); fft(s7, -1);
    for (int i=0; i<tot; ++i) {
        long long a = s5[i].x / tot + .5, b = s4[i].x / tot + .5, c = s3[i].x / tot + .5,
                  d = s2[i].x / tot + .5, e = s6[i].x / tot + .5, g = s7[i].x / tot + .5;
        if (i%5==0 && i/5<=x && f[i/5]) --a, --b, --c, --d, --e, --g;
        g -= b + 2*e; c -= 2*b + e; d -= 3*(b + c + g) + 4*e;
        a = (a - 5*b - 10*(c + d + e) - 15*g + 60) / 120;
        if (a > 0) cout << i << ": " << a << endl;
    }
}

void solve() {
    int m, p, v; cin >> m >> p;
    memset(f, x = 0, sizeof(f));
    while (m--) cin >> v, x = max(x, v), f[v] = true;
    for (m=x*p, tot=1; tot <= m; tot<<=1);
    for (int i=0; i<tot; ++i) s1[i] = {i<=x && f[i] ? 1. : 0., 0.};
    fft(s1, 1);
    for (int i=0; i<tot; ++i) s2[i] = s1[i] * s1[i];
    cout << "Case #" << ++kase << ':' << endl;
    if (p == 1) solve1();
    else if (p == 2) solve2();
    else if (p == 3) solve3();
    else if (p == 4) solve4();
    else solve5();
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}