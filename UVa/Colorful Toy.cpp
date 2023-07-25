/**
 * LA7056/hdu5080
 * 玩具涂色
 * 鞍山2014
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 1000000007
#define N 52
int x[N], y[N], d[N], t[N], p[N], a[N][N], u[N*N>>1], v[N*N>>1], e[N][N], cx, cy, m, n, c, cc, s;
long long pow[N], inv[] = {-1, 1, 500000004, 333333336, 250000002}, ans;

bool find() {
    for (int i=0; i<n; ++i) if (x[i]==cx && y[i]==cy) return true;
    return false;
}

void add(int i, int dd) {
    for (int j=0; j<s; ++j) if (dd == d[j]) {
        a[j][t[j]++] = i;
        return;
    }
    a[s][0] = i; d[s] = dd; t[s++] = 1;
}

void rot_90() {
    long long r = 1;
    for (int i=0; i<s; ++i) {
        if (t[i] == 1) {
            r = r*c % M; p[a[i][0]] = a[i][0];
        } else {
            if (t[i] & 3) return;
            for (int j=0; j<t[i]; ++j) {
                bool ok = false; int x1 = x[a[i][j]]-cx, y1 = y[a[i][j]]-cy;
                for (int k=0; k<t[i] && !ok; ++k) {
                    int x2 = x[a[i][k]]-cx, y2 = y[a[i][k]]-cy;
                    if (x1*y2 - x2*y1 == d[i]) ok = true, p[a[i][j]] = a[i][k];
                }
                if (!ok) return;
            }
            r = r * pow[t[i]>>2] % M;
        }
    }
    for (int i=0; i<m; ++i) if (!e[p[u[i]]][p[v[i]]]) return;
    ans = (ans + r) % M; ++ cc;
}

void rot_180() {
    long long r = 1;
    for (int i=0; i<s; ++i) {
        if (t[i] == 1) {
            r = r*c % M; p[a[i][0]] = a[i][0];
        } else {
            if (t[i] & 1) return;
            for (int j=0; j<t[i]; ++j) {
                bool ok = false; int x1 = x[a[i][j]]-cx, y1 = y[a[i][j]]-cy;
                for (int k=0; k<t[i] && !ok; ++k) {
                    int x2 = x[a[i][k]]-cx, y2 = y[a[i][k]]-cy;
                    if (x1*x2 + y1*y2 == -d[i]) ok = true, p[a[i][j]] = a[i][k];
                }
                if (!ok) return;
            }
            r = r * pow[t[i]>>1] % M;
        }
    }
    for (int i=0; i<m; ++i) if (!e[p[u[i]]][p[v[i]]]) return;
    ans = (ans + r) % M; ++ cc;
}

void rot_270() {
    long long r = 1;
    for (int i=0; i<s; ++i) {
        if (t[i] == 1) {
            r = r*c % M; p[a[i][0]] = a[i][0];
        } else {
            if (t[i] & 3) return;
            for (int j=0; j<t[i]; ++j) {
                bool ok = false; int x1 = x[a[i][j]]-cx, y1 = y[a[i][j]]-cy;
                for (int k=0; k<t[i] && !ok; ++k) {
                    int x2 = x[a[i][k]]-cx, y2 = y[a[i][k]]-cy;
                    if (x2*y1 - x1*y2 == d[i]) ok = true, p[a[i][j]] = a[i][k];
                }
                if (!ok) return;
            }
            r = r * pow[t[i]>>2] % M;
        }
    }
    for (int i=0; i<m; ++i) if (!e[p[u[i]]][p[v[i]]]) return;
    ans = (ans + r) % M; ++ cc;
}

long long solve() {
    memset(e, cx = cy = 0, sizeof(e));
    cin >> n >> m >> c;
    pow[0] = 1; for (int i=1; i<=n; ++i) pow[i] = c*pow[i-1] % M;
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i], x[i] <<= 1, y[i] <<= 1, cx += x[i], cy += y[i];
    for (int i=0; i<m; ++i) cin >> u[i] >> v[i], --u[i], --v[i], e[u[i]][v[i]] = e[v[i]][u[i]] = 1;
    if (n==1 || cx%n || cy%n) return pow[n];
    cx /= n; cy /= n;
    if ((n&1 && !find()) || (~n&1 && find())) return pow[n];
    for (int i=s=0; i<n; ++i) add(i, (x[i]-cx)*(x[i]-cx) + (y[i]-cy)*(y[i]-cy));
    for (int i=0; i<s; ++i) if (d[i] && t[i]&1) return pow[n];
    ans = pow[n]; cc = 1;
    rot_90(); rot_180(); rot_270();;
    return ans * inv[cc] % M;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}
