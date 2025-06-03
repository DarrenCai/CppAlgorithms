/**
 * UVa12298
 * 超级扑克II
 */

#include <iostream>
#include <cmath>
using namespace std;

#define M 50020
#define N 1<<17
int rev[N] = {0}, na, nb, nc, tot; bool f[M] = {false};
struct complex {
    double x, y;
    complex operator+ (const complex &t) const {
        return {x + t.x, y + t.y};
    }
    complex operator- (const complex &t) const {
        return {x - t.x, y - t.y};
    }
    complex operator* (const complex &t) const {
        return {x * t.x - y * t.y, x * t.y + y * t.x};
    }

} a[4][N];

void fft(complex (&a)[N], int inv) {
    for (int i=0; i<tot; ++i) if (i < rev[i]) {
        complex t = a[i]; a[i] = a[rev[i]]; a[rev[i]] = t;
    }
    for (int mid=1; mid<tot; mid<<=1) for (int i=0, k=mid<<1; i<tot; i+=k) {
        complex wk = {1., 0.};
        for (int j=0; j<mid; ++j, wk = {cos(j*M_PI / mid), inv * sin(j*M_PI / mid)}) {
            complex x = a[i + j], y = wk * a[i + j + mid];
            a[i + j] = x + y; a[i + j + mid] = x - y;
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
    for (int i=0; i<tot; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
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