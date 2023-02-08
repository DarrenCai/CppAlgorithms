/**
 * UVa1478/LA5028
 * Delta脑电波
 * Tianjin 2010
 */

#include <iostream>
using namespace std;

#define N 5001
struct uintg {
    int v[12], n;
    void operator= (int x) {
        v[0] = x; n = 1;
    }
    void operator= (const uintg& x) {
        n = x.n;
        for (int i=0; i<n; ++i) v[i] = x.v[i];
    }
    void mod() {
        if (n > 11 && v[11] > 9) {
            v[11] %= 10;
            if (!v[11]) n = 11;
        }
    }
    void operator+= (const uintg& x) {
        int r = 0, m = max(x.n, n);
        for (int i=0; i<m; ++i) {
            r += (i<n ? v[i] : 0) + (i<x.n ? x.v[i] : 0);
            r > 999999999 ? (v[i] = r-1000000000, r = 1) : (v[i] = r, r = 0);
        }
        n = m+r;
        if (r) v[m] = r;
    }
    uintg operator* (const uintg& x) {
        uintg t; t.n = min(n + x.n - 1, 12); long long r = 0;
        for (int i=0; i<t.n; ++i) {
            long long y = r; r = 0;
            for (int j=0; j<=i && j<n; ++j) {
                if (i-j < x.n) y += x.v[i-j] * (long long)v[j];
                if (y > 999999999) r += y / 1000000000, y %= 1000000000;
            }
            t.v[i] = y;
        }
        if (r && t.n<12) t.v[t.n++] = r;
        t.mod();
        return t;
    }
    void print(int x, int c = 1) {
        if (c < 9) print(x/10, c+1);
        cout << x%10;
    }
    void print() {
        cout << v[n-1];
        for (int i=n-2; i>=0; --i) print(v[i]);
        cout << endl;
    }
} f[N][N];

void solve(int n) {
    if (n < N) return f[n][0].print();
    uintg ans; ans.n = 0;
    for (int i=n>>1, a=i, b=n-i; i>=0; --i) ans += f[a][i] * f[b][i];
    ans.mod();
    ans.print();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    f[0][0] = 1; f[1][0] = 1; f[1][1] = 1;
    for (int i=2; i<N; ++i) {
        f[i][i] = 1;
        for (int j=0; j<i; ++j) {
            f[i][j] = f[i-1][j];
            if (j > 0) f[i][j] += f[i-1][j-1];
            if (j+2 <= i) f[i][j] += f[i-1][j+1];
            f[i][j].mod();
        }
    }
    int n;
    while (cin >> n) solve(n);
    return 0;
}