/**
 * UVa12298
 * 超级扑克II
 */

#include <iostream>
#include <cmath>
using namespace std;

#define M 50020
#define N 1<<17
int na, nb, nc, tot; bool f[M] = {false};
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

} a[4][N];

void fft(complex (&a)[N], int inv) {
    for (int i=0, j=0, k; i<tot; ++i) {
        if(j > i) {complex t = a[i]; a[i] = a[j]; a[j] = t;}
        for (k = tot; j & (k >>= 1); j &= ~k);
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
    int bit = 0; tot = (nb<<1) | 1;
    while ((1 << bit) < tot) ++bit;
    tot = 1 << bit;
    for (int i=0; i<tot; ++i) a[0][i] = a[1][i] = a[2][i] = a[3][i] = {i<nb && f[i] ? 1. : 0., 0.};
    while (nc--) {
        int v; char h; cin >> v >> h;
        a[h == 'S' ? 0 : (h == 'H' ? 1 : (h == 'C' ? 2 : 3))][v].x = 0.;
    }
    for (int i=0; i<4; ++i) fft(a[i], 1);
    for (int i=0; i<tot; ++i) a[0][i] = a[0][i] * a[1][i], a[2][i] = a[2][i] * a[3][i];
    fft(a[0], -1); fft(a[2], -1);
    for (int i=0; i<tot; ++i) a[0][i] = {i<nb ? a[0][i].x / tot : 0., 0.}, a[2][i] = {i<nb ? a[2][i].x / tot : 0., 0.};
    fft(a[0], 1); fft(a[2], 1);
    for (int i=0; i<tot; ++i) a[0][i] = a[0][i] * a[2][i];
    fft(a[0], -1);
    for (int i=na; i<=nb; ++i) cout << (long long)(a[0][i].x / tot + .5) << endl;
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=2; i*i<M; ++i) if (!f[i]) for (int j=i*i; j<M; j+=i) f[j] = true;
    while (cin >> na >> nb >> nc && (na || nb || nc)) solve();
    return 0;
}