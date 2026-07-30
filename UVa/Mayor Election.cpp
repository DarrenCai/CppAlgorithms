/**
 * UVa11640
 * 海报张贴
 */

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

#define M 786433
#define L 100001
#define T 1<<17
#define X 2010
#define N 50
#define P 11
int d[X][P], c[P], n, tot = T;

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
} s[N][T];

void fft(complex (&a)[T], int inv) {
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
    cin >> n;
    for (int i=0; i<n; ++i) {
        int p, l, u; cin >> p >> l >> u;
        memset(d, 0, sizeof(d));
        for (int j=0; j<p; ++j) cin >> c[j], d[1][j] = 1;
        for (int j=2; j<=u; ++j) for (int k=0; k<p; ++k) {
            for (int x=0; x<p; ++x) if (x != k) for (int t=1; t<=c[x] && t<j; ++t) d[j][k] = (d[j][k] + d[j-t][x]) % M;
        }
        for (int j=0; j<l; ++j) s[i][j] = {0., 0.};
        for (int j=l; j<=u; ++j) {
            int f = j<1 ? 1 : 0;
            for (int x=0; x<p; ++x) for (int t=1; t<=c[x] && t<=j; ++t) f = (f + d[j-t+1][x]) % M;
            s[i][j] = {1.*f, 0.};
        }
        for (int j=u+1; j<tot; ++j) s[i][j] = {0., 0.};
    }
    for (int i=1; i<n; ++i) {
        fft(s[0], 1); fft(s[i], 1);
        for (int j=0; j<tot; ++j) s[0][j] = s[0][j] * s[i][j];
        fft(s[0], -1);
        for (int j=0; j<tot; ++j) if (j < L) {
            long long f = s[0][j].x / tot + .5;
            s[0][j] = {1.*(f % M), 0.};
        } else s[0][j] = {0., 0.};
    }
    int q; cin >> q;
    for (int i=1; i<=q; ++i) {
        int x; cin >> x;
        cout << "Query " << i << ": " << int(s[0][x].x) << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int i=1; i<=t; ++i) {
        cout << "Case #" << i << ':' << endl;
        solve();
        cout << endl;
    }
    return 0;
}