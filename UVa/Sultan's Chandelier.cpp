/**
 * UVa11540
 * 苏丹的吊灯
 */

#include <iostream>
using namespace std;

#define M 1000000007
#define N 102

int inv[N], t; long long ans[N];

int gcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1; y = 0; return a;
    } else {
        int g = gcd(b, a%b, y, x);
        y -= a/b*x;
        return g;
    }
}

struct chd {
    int c[N], n;
    chd():n(0) {}
    bool operator== (const chd& rhs) const {
        if (n != rhs.n) return false;
        for (int i=0, cc; i<n; ++i) {
            for (int j=cc=0; j<n; ++j) {
                if (c[(i+j)%n] != rhs.c[j]) break;
                ++ cc;
            }
            if (cc == n) return true;
        }
        return n == 0;
    }
} chs[N];

int find(const chd& r) {
    for (int i=0; i<t; ++i) if (r == chs[i]) return i;
    chs[t] = r;
    return t++;
}

int build() {
    chd r; char _; cin >> _;
    if (cin.get() == ']') return find(r);
    cin.unget();
    do {
        r.c[r.n++] = build();
    } while (cin.get() == ',');
    return find(r);
}

long long rot(const chd& r, int a) {
    long long v = 1; bool vis[N] = {0};
    for (int i=0; i<r.n; ++i) if (!vis[i]) {
        for (int j=i; !vis[j]; j = (j+a) % r.n) {
            if (r.c[i] != r.c[j]) return -1;
            vis[j] = true;
        }
        v = v * ans[r.c[i]] % M;
    }
    return v;
}

void calc(int i) {
    long long &r = ans[i] = 0; chd &s = chs[i]; int cc = 0;
    for (int j=0; j<s.n; ++j) {
        int v = rot(s, j);
        if (v >= 0) r += v, ++cc;
    }
    r = r % M * inv[cc] % M * ans[0] % M;
}

long long solve() {
    t = 0;
    build();
    cin >> ans[0];
    for (int i=1; i<t; ++i) calc(i);
    return ans[t-1];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=1, x, y; i<N; i++) {
        gcd(i, M, x, y);
        inv[i] = (x+M) % M;
    }
    int t; cin >> t;
    for (int k=1; k<=t; ++k) cout << "Case #" << k << ": " << solve() << endl;
    return 0;
}
