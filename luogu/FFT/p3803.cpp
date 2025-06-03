/**
 * P3803 【模板】多项式乘法（FFT）
 */

#include <iostream>
#include <cmath>
using namespace std;

#define N 1<<21
int rev[N], res[N], tot, m, n;
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

} a[N], b[N];

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
    cin >> n >> m;
    for (int i=0; i<=n; ++i) cin >> a[i].x, a[i].y = 0.;
    for (int i=0; i<=m; ++i) cin >> b[i].x, b[i].y = 0.;
    int bit = 0;
    while ((1 << bit) < n + m + 1) ++bit;
    tot = 1 << bit;
    for (int i=0; i<tot; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    fft(a, 1); fft(b, 1);
    for (int i=0; i<tot; ++i) a[i] = a[i] * b[i];
    fft(a, -1);
    for (int i=0, j=m+n; i<=j; ++i) res[i]  = a[i].x / tot + 0.5;
    cout << res[0];
    for (int i=1, j=m+n; i<=j; ++i) cout << ' ' << res[i];
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}