/**
 * UVa11443
 * 网格里的树
 */

#include <iostream>
#include <cstring>
using namespace std;

#define T 1430
#define M 200
#define N 8

int d[2][T], f[M*N], p[1<<(3*N-5)], r[T], a[N], b[N+1], c, m, n, md, t; char s[M<<1][N<<1];

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

void decode(int x) {
    for (int i=n-1; i>=0; --i) a[i] = x&7, x >>= 3;
}

bool valid(int x) {
    decode(x);
    for (int i=0; i<n; ++i) for (int j=i+2; j<n; ++j) if (a[i] == a[j])
        for (int k=i+1; k<j; ++k) if (a[i] != a[k]) for (int t=j+1; t<n; ++t) if (a[k] == a[t]) return false;
    return true;
}

int rep() {
    for (int i=0, j=0, k; i<n; ++i) {
        for (k=0; k<i; ++k) if (a[k] == a[i]) break;
        if (k == i) b[a[i]] = j++;
    }
    int y = 0;
    for (int i=0; i<n; ++i) y = y<<3 | b[a[i]];
    return y;
}

int rep(int x) {
    decode(x);
    return rep();
}

int cnt(int x) {
    int c = 0;
    for (int i=0; i<n; ++i) if (a[i] == x) ++c;
    return c;
}

void solve() {
    cin >> m >> n >> md; cin.get();
    for (int i=0, r=(m<<1)-1; i<r; ++i) cin.getline(s[i], n<<1);
    for (int i=0, k=0; i<m; ++i) for (int j=0; j<n; ++j, ++k) {
        f[k] = k;
        if (i && s[(i<<1)-1][j<<1] != ' ') f[k] = k-n;
        if (j && s[i<<1][(j<<1)-1] != ' ') {
            int u = find(k-1), v = find(k);
            if (u == v) {
                cout << "Impossible" << endl;
                return;
            }
            f[v] = u;
        }
    }
    for (int i=c=0, x=1<<(3*n-5); i<x; ++i) if (valid(i) && rep(i) == i) r[p[i] = c++] = i;
    memset(d[0], 0, sizeof(d[0])); d[0][c-1] = 1;
    for (int i=0, e=1; i<m; ++i) for (int j=0; j<n; ++j, e^=1) {
        memset(d[e], 0, sizeof(d[e]));
        for (int k=0; k<c; ++k) if (d[e^1][k]) {
            decode(r[k]);
            const int t = a[j], l = j ? a[j-1] : -1, dd = d[e^1][k];
            if (!j || s[i<<1][(j<<1)-1] == ' ') d[e][k] = (d[e][k] + dd) % md;
            if (cnt(t) != 1) {
                if (j && (!i || s[(i<<1)-1][j<<1] == ' ')) {
                    a[j] = l;
                    int &f = d[e][p[rep()]]; f = (f + dd) % md;
                }
                if ((!i || s[(i<<1)-1][j<<1] == ' ') && (!j || s[i<<1][(j<<1)-1] == ' ')) {
                    decode(r[k]); a[j] = n;
                    int &f = d[e][p[rep()]]; f = (f + dd) % md;
                }
            }
            if (l >= 0 && l != t) {
                decode(r[k]);
                for (int b=0; b<n; ++b) if (a[b] == t) a[b] = l;
                int &f = d[e][p[rep()]]; f = (f + dd) % md;
            }
        }
    }
    cout << d[m*n&1][0] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cin >> t;
    while (t--) solve();
    return 0;
}