/**
 * UVa1404/LA3998
 * 素数k元组
 * Danang 2007
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 212
#define N 44722
#define C 5000
#define T 10000010
bool f[T] = {false}; int prim[C], p[T], c = 1;

void solve() {
    int a, b, k, s, cnt = 0, cc = 0; cin >> a >> b >> k >> s;
    memset(f, 0, sizeof(f));
    for (int i=0; i<c; ++i) {
        int x = (a+prim[i]-1) / prim[i];
        if (x < 2) ++x;
        x *= prim[i];
        while (x <= b) f[x-a] = true, x += prim[i];
    }
    for (int x=a; x<=b; ++x) if (!f[x-a]) p[cc++] = x;
    for (int i=--k; i<cc; ++i) if (p[i]-p[i-k] == s) ++cnt;
    cout << cnt << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    prim[0] = 2;
    for (int i=3; i<M; i+=2) if (!f[i]) for (int j=i*i, k=i<<1; j<N; j+=k) f[j] = true;
    for (int i=3; i<N; i+=2) if (!f[i]) prim[c++] = i;
    int t; cin >> t;
    while (t--) solve();
    return 0;
}