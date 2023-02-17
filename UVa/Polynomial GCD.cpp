/**
 * UVa10951
 * 多项式的最大公约数
 */

#include <iostream>
using namespace std;

#define M 38
#define N 1500
#define D 102
int inv[N][N], n, kase = 0; bool flg[N] = {false};

int pow_mod(int a, int n, int m) {
    int ans = 1;
    for (int k=n; k; k>>=1, a = a*a % m) if (k & 1) ans = ans*a % m;
    return ans;
}

struct poly {
    int c[D], d;
    void read() {
        cin >> d;
        for (int i=d; i>=0; --i) cin >> c[i];
    }
    bool zero() {
        return d==0 && c[0]==0;
    }
    poly& operator% (const poly& p) {
        for (int i=d; i>=p.d; --i) if (c[i]) {
            int x = c[i] * inv[p.c[p.d]][n] % n;
            for (int j=p.d; j>=0; --j) c[i-p.d+j] = (c[i-p.d+j] - x*p.c[j]%n + n) % n;
        }
        d = p.d;
        while (d && c[d]==0) --d;
        return *this;
    }
} f, g;

poly& gcd(poly& f, poly& g)  {
    if (f.zero()) return g;
    if (g.zero()) return f;
    if (f.d > g.d) return gcd(g, f%g);
    return gcd(f, g%f);
}

void solve() {
    cout << "Case " << ++kase << ':';
    f.read();
    g.read();
    poly& r = gcd(f, g);
    if (r.c[r.d] > 1) for (int i=r.d, x=r.c[i]; i>=0; --i) r.c[i] = r.c[i]*inv[x][n] % n;
    cout << ' ' << r.d;
    for (int i=r.d; i>=0; --i) cout << ' ' << r.c[i];
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=2; i<M; ++i) if (!flg[i]) for (int j=i*i; j<N; j+=i) flg[j] = true;
    for (int i=2; i<N; ++i) if (!flg[i]) {
        inv[1][i] = 1;
        for (int j=2; j<i; ++j) inv[j][i] = pow_mod(j, i-2, i);
    }
    while (cin>>n && n) solve();
    return 0;
}