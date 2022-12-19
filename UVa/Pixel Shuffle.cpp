/**
 * UVa1156/LA3510
 * 像素混合
 * CERC 2005
 */

#include <iostream>
using namespace std;

#define N 1<<20
int f[N], g[N], n, m, h, t; bool vis[N];

void calc_g(const char *s) {
    if (s[0] == 'r') {
        bool f = s[3] == '-';
        for (int r=0; r<n; ++r) for (int c=0; c<n; ++c) g[r*n+c] = (f ? c : n-1-c)*n + (f ? n-1-r : r);
    } else if (s[0] == 's') {
        for (int r=0; r<n; ++r) for (int c=0; c<n; ++c) g[r*n+c] = r*n + n-1-c;
    } else if (s[1] == 'h') {
        for (int r=0; r<h; ++r) for (int c=0; c<n; ++c) g[r*n+c] = r*n + c;
        for (int r=h; r<n; ++r) for (int c=0; c<n; ++c) g[r*n+c] = r*n + n-1-c;
    } else if (s[1] == 'v') {
        for (int r=0; r<h; ++r) for (int c=0; c<n; ++c) g[r*n+c] = r*n + c;
        for (int r=h; r<n; ++r) for (int c=0; c<n; ++c) g[r*n+c] = (n+h-r-1)*n + c;
    } else if (s[0] == 'd') {
        if (s[3] == '-') {
            for (int r=0; r<h; ++r) for (int c=0; c<n; ++c) g[r*n+c] = (r<<1)*n + c;
            for (int r=h; r<n; ++r) for (int c=0; c<n; ++c) g[r*n+c] = ((r<<1)-n+1)*n + c;
        } else {
            for (int r=0; r<n; r+=2) for (int c=0; c<n; ++c) g[r*n+c] = (r>>1)*n + c;
            for (int r=1; r<n; r+=2) for (int c=0; c<n; ++c) g[r*n+c] = ((n+r)>>1)*n + c;
        }
    } else if (s[3] == '-') {
        for (int r=0; r<n; r+=2) for (int c=0; c<n; ++c) g[r*n+c] = (c&1 ? r+1 : r)*n + (c>>1);
        for (int r=1; r<n; r+=2) for (int c=0; c<n; ++c) g[r*n+c] = (c&1 ? r : r-1)*n + (c>>1)+h;
    } else for (int r=0; r<n; ++r) {
        for (int c=0; c<h; ++c) g[r*n+c] = (r&1 ? r-1 : r)*n + (r&1 ? (c<<1)+1 : c<<1);
        for (int c=h; c<n; ++c) g[r*n+c] = (r&1 ? r : r+1)*n + (r&1 ? (c<<1)+1-n : (c-h)<<1);
    }
}

void mul() {
    char s[8]; cin >> s;
    if (cin.get() == ' ') mul();
    if (s[0] == 'i') return;
    calc_g(s);
    for (int i=0; i<m; ++i) f[i] = g[f[i]];
}

int gcd(int a, int b) {
    if (a > b) return gcd(b, a);
    if (a < 0) return gcd(-a, b);
    if (a == 0) return b;
    if (a & 1) {
        if (b & 1) return gcd(a, (b-a)>>1);
        return gcd(a, b >> 1);
    } else {
        if (b & 1) return gcd(a >> 1, b);
        return gcd(a >> 1, b >> 1) << 1;
    }
}

void solve() {
    cin >> n; m = n*n; h = n>>1;
    for (int i=0; i<m; ++i) f[i] = i, vis[i] = false;
    mul();
    long long g = 1;
    for (int i=0; i<m; ++i) if (!vis[i]) {
        int l = vis[i] = 1;
        for (int j=f[i]; !vis[j]; j=f[j]) ++l, vis[j] = true;
        if (l > 1) g = g*l / gcd(g, l);
    }
    cout << g << endl;
    if (t) cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cin >> t;
    while (t--) solve();
    return 0;
}