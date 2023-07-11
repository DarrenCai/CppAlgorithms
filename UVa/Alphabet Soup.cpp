/**
 * UVa12387/LA5819
 * 字母浓汤
 * SWERC 2011
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define M 100000007
#define N 360000
#define T 104

int d[] = {1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, 16, 18, 20, 24, 25, 30, 32, 36, 40, 45, 48, 50, 60, 64,
           72, 75, 80, 90, 96, 100, 120, 125, 144, 150, 160, 180, 192, 200, 225, 240, 250, 288, 300,
           320, 360, 375, 400, 450, 480, 500, 576, 600, 625, 720, 750, 800, 900, 960, 1000, 1125, 1200,
           1250, 1440, 1500, 1600, 1800, 1875, 2000, 2250, 2400, 2500, 2880, 3000, 3600, 3750, 4000,
           4500, 4800, 5000, 5625, 6000, 7200, 7500, 8000, 9000, 10000, 11250, 12000, 14400, 15000,
           18000, 20000, 22500, 24000, 30000, 36000, 40000, 45000, 60000, 72000, 90000, 120000, 180000};
int a[N], inv[N+1], s, n, cc; long long pow[N+1], ans; bool vis[N];

int gcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1; y = 0; return a;
    } else {
        int g = gcd(b, a%b, y, x);
        y -= a/b*x;
        return g;
    }
}

int gcd(int a, int b) {
    return b==0 ? a : gcd(b, a%b);
}

void rot(int s, int d) {
    for (int i=1; i<n; ++i) if ((a[(i+s) % n] - a[i] + N) % N != d) return;
    int g = gcd(s, n), p = n/g;
    for (int i=s; i<n; i+=s) vis[i] = true, ans += pow[g*gcd(p, i/s)], ++cc;
}

long long solve() {
    for (int i=0; i<n; ++i) cin >> a[i], vis[i] = false;
    for (int i=1; i<=n; ++i) pow[i] = pow[i-1]*s % M;
    sort(a, a+n);
    for (int i=1; i<n; ++i) a[i] -= a[0];
    a[0] = 0;
    ans = pow[n]; cc = 1;
    for (int i=0; i<T; ++i) {
        int j = lower_bound(a, a+n, d[i]) - a;
        if (j<n && a[j]==d[i] && !vis[j]) rot(j, d[i]);
    }
    return ans % M * inv[cc] % M;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    pow[0] = 1;
    for (int i=1, x, y; i<=N; ++i) {
        gcd(i, M, x, y);
        inv[i] = (x+M) % M;
    }
    ios::sync_with_stdio(false);
    while (cin >> s >> n && s >= 0) cout << solve() << endl;
    return 0;
}
