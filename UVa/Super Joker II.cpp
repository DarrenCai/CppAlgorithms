/**
 * UVa12298
 * 超级扑克II
 */

#include <iostream>
#include <cmath>
using namespace std;

#define M 1<<17
#define N 50001
int a, b, c, tot; bool f[N];

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
} s[4][M];

void fft(complex (&a)[M], int inv) {
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

void solve() {
    for (int t = (b<<1) + (tot=1); tot < t; tot <<= 1);
    for (int i=0; i<tot; ++i) s[0][i] = s[1][i] = s[2][i] = s[3][i] = {i<b && f[i] ? 1. : 0., 0.};
    while (c--) {
        int p; char ch; cin >> p >> ch;
        s[ch=='S' ? 0 : (ch=='H' ? 1 : (ch=='C' ? 2 : 3))][p].x = 0.;
    }
    for (int i=0; i<4; ++i) fft(s[i], 1);
    for (int i=0; i<tot; ++i) s[0][i] = s[0][i] * s[2][i], s[1][i] = s[1][i] * s[3][i];
    fft(s[0], -1); fft(s[1], -1);
    for (int i=0; i<tot; ++i)
        s[0][i].x = i<b ? s[0][i].x / tot : 0., s[1][i].x = i<b ? s[1][i].x / tot : 0., s[0][i].y = s[1][i].y = 0.;
    fft(s[0], 1); fft(s[1], 1);
    for (int i=0; i<tot; ++i) s[0][i] = s[0][i] * s[1][i];
    fft(s[0], -1);
    for (int i=a; i<=b; ++i) cout << (long long)(s[0][i].x / tot + 0.5) << endl;
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=0; i<N; ++i) f[i] = false;
    for (int i=2; i<N; ++i) if (!f[i]) for (int j=i<<1; j<N; j+=i) f[j] = true;
    while (cin >> a >> b >> c && (a || b || c)) solve();
}