/**
 * UVa12232/LA4487
 * 异或
 * Wuhan 2009
 */

#include <iostream>
using namespace std;

#define K 16
#define N 20020
int f[N], e[N], x[N], p[K], n, q, k, t, cc, kase = 0; bool vis[K];

int find(int x) {
    int y = f[x];
    if (y != x) f[x] = find(y), e[x] ^= e[y];
    return f[x];
}

void query() {
    cin >> k; for (int i=0; i<k; ++i) cin >> p[i], vis[i] = false;
    if (cc) return;
    int ans = 0;
    for (int i=0; i<k; ++i) if (!vis[i]) {
        int c = 0, y = find(p[i]);
        for (int j=0; j<k; ++j) if (find(p[j]) == y) ++c, vis[j] = true, ans ^= e[p[j]];
        if (c & 1) {
            if (x[y] < 0) {
                cout << "I don't know." << endl;
                return;
            }
            ans ^= x[y];
        }
    }
    cout << ans << endl;
}

void solve() {
    for (int i=t=cc=0; i<n; ++i) f[i] = i, e[i] = 0, x[i] = -1;
    cout << "Case " << ++kase << ':' << endl;
    while (q--) {
        char c; cin >> c;
        if (c == 'I') {
            int p, q, v; cin >> p >> q; ++t;
            if (cin.peek() == ' ') {
                cin >> v;
                if (cc) continue;
                int y = find(p), z = find(q);
                if (y == z) {
                    if ((e[p]^e[q]) != v) cout << "The first " << (cc = t) << " facts are conflicting." << endl;
                } else {
                    if (x[p]<0 && x[y]>=0) x[p] = x[y]^e[p];
                    if (x[q]<0 && x[z]>=0) x[q] = x[z]^e[q];
                    if (x[p]>=0 && x[q]>=0) {
                        if ((x[p]^x[q]) != v) cout << "The first " << (cc = t) << " facts are conflicting." << endl;
                    } else {
                        f[y] = z; e[y] = e[p]^e[q]^v;
                        if (x[y] >= 0) x[z] = e[y]^x[y];
                    }
                }
            } else {
                if (cc) continue;
                int y = find(p);
                if (x[p]<0 && x[y]>=0) x[p] = x[y]^e[p];
                if (x[p] >= 0) {
                    if (x[p] != q) cout << "The first " << (cc = t) << " facts are conflicting." << endl;
                } else x[y] = e[p]^q;
            }
        } else query();
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin>>n>>q && n) solve();
    return 0;
}