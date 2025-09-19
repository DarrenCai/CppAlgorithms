/**
 * UVa1602/LA3224
 * 网格动物
 * NEERC 2004
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define T 4660
#define N 11
int f[N][N+1][N], t[N], n, w, h;

struct node {
    int p[N], w, h;
    bool eq(const node &e, const int n) const {
        for (int i=0; i<n; ++i) if (p[i] != e.p[i]) return false;
        return true;
    }
    node rotate(const int n) const {
        node t; t.w = h; t.h = w;
        for (int i=0; i<n; ++i) {
            int r = p[i]&15, c = h-1 - (p[i]>>4);
            t.p[i] = r<<4 | c;
        }
        sort(t.p, t.p+n);
        return t;
    }
    node flip_h(const int n) const {
        node t; t.w = w; t.h = h;
        for (int i=0; i<n; ++i) {
            int r = h-1 - (p[i]>>4), c = p[i]&15;
            t.p[i] = r<<4 | c;
        }
        sort(t.p, t.p+n);
        return t;
    }
    node flip_v(const int n) const {
        node t; t.w = w; t.h = h;
        for (int i=0; i<n; ++i) {
            int r = p[i]>>4, c = w-1 - (p[i]&15);
            t.p[i] = r<<4 | c;
        }
        sort(t.p, t.p+n);
        return t;
    }
} s[N][T];

bool exist(const int n, const int t) {
    node e = s[n][t-1];
    for (int i=0; i<4; ++i, e = e.rotate(n)) {
        node h = e.flip_h(n), v = e.flip_v(n);
        for (int j=t-2; j>=0; --j) {
            const node &f = s[n][j];
            if (e.w != f.w || e.h != f.h) continue;
            if (e.eq(f, n) || h.eq(f, n) || v.eq(f, n)) return true;
        }
    }
    return false;
}

void add(const node &e, int n, int v) {
    int &c = t[n], k = lower_bound(e.p, e.p+n-1, v) - e.p;
    if (k < n-1 && e.p[k] == v) return;
    node& f = s[n][c++]; f.w = e.w; f.h = e.h;
    for (int i=0; i<k; ++i) f.p[i] = e.p[i];
    for (int i=n-1; i>k; --i) f.p[i] = e.p[i-1];
    f.p[k] = v;
    if (exist(n, c)) --c;
}

void generate() {
    for (int n=1; n<N; ++n) {
        if (n > 1) {
            for (int &k = t[n] = 0, i=t[n-1]-1; i>=0; --i) {
                const node& e = s[n-1][i];
                for (int j=n-2; j>=0; --j) {
                    int r = e.p[j]>>4, c = e.p[j]&15;
                    if (r == 0) {
                        node& f = s[n][k++]; f.w = e.w; f.h = e.h+1;
                        for (int x=n-1; x>0; --x) f.p[x] = e.p[x-1] + 16;
                        f.p[0] = c;
                        if (exist(n, k)) --k;
                    } else if (r > 0) add(e, n, e.p[j] - 16);
                    if (r == e.h-1) {
                        node& f = s[n][k++]; f.w = e.w; f.h = e.h+1;
                        for (int x=n-2; x>=0; --x) f.p[x] = e.p[x];
                        f.p[n-1] = e.p[j] + 16;
                        if (exist(n, k)) --k;
                    } else if (r < e.h-1) add(e, n, e.p[j] + 16);
                    if (c == 0) {
                        node& f = s[n][k++]; f.w = e.w+1; f.h = e.h;
                        for (int x=0; x<j; ++x) f.p[x] = e.p[x] + 1;
                        for (int x=n-1; x>j; --x) f.p[x] = e.p[x-1] + 1;
                        f.p[j] = e.p[j];
                        if (exist(n, k)) --k;
                    } else if (c > 0) add(e, n, e.p[j] - 1);
                    if (c == e.w-1) {
                        node& f = s[n][k++]; f.w = e.w+1; f.h = e.h;
                        for (int x=0; x<=j; ++x) f.p[x] = e.p[x];
                        for (int x=n-2; x>j; --x) f.p[x+1] = e.p[x];
                        f.p[j+1] = e.p[j] + 1;
                        if (exist(n, k)) --k;
                    } else add(e, n, e.p[j] + 1);
                }
            }
        } else s[1][0].w = s[1][0].h = 1, s[1][0].p[0] = 0, t[1] = 1;
        for (int h=1; h<=n; ++h) for (int w=h; w<=n; ++w) {
            int &a = f[w][h][n] = 0, &b = f[h][w][n] = 0;
            if (w*h >= n) for (int i=t[n]-1; i>=0; --i) {
                int hi = min(s[n][i].w, s[n][i].h), wi = max(s[n][i].w, s[n][i].h);
                if (hi <= h && wi <= w) {
                    if (h < w) ++b;
                    ++a;
                }
            }
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    generate();
    while (cin >> n >> w >> h) cout << f[w][h][n] << endl;
    return 0;
}