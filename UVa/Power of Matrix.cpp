/**
 * UVa11149
 * 矩阵的幂
 */

#include <iostream>
using namespace std;

#define M 10
#define N 41
int a[N][N], f[N][N], t[N][N], p[N][N], ans[N][N], n, k;

void copy(int (&a)[N][N], const int (&b)[N][N]) {
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) a[i][j] = b[i][j];
}

void mul(int (&a)[N][N], const int (&b)[N][N]) {
    copy(p, a);
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j)
        for (int k = a[i][j] = 0; k<n; ++k) a[i][j] = (a[i][j] + p[i][k]*b[k][j]) % M;
}

void add(int (&a)[N][N], const int (&b)[N][N]) {
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) a[i][j] = (a[i][j] + b[i][j]) % M;
}

void add_identity(int (&a)[N][N], const int (&b)[N][N]) {
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) a[i][j] = i!=j ? b[i][j] : (b[i][j] + 1) % M;
}

void solve() {
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) {
        cin >> a[i][j];
        f[i][j] = a[i][j] %= M;
        ans[i][j] = 0;
    }
    for (int x=k; x; x>>=1) {
        if (x & 1) mul(ans, a), add(ans, f);
        add_identity(t, a); mul(f, t);
        copy(t, a); mul(a, t);
    }
    for (int i=0; i<n; ++i) {
        cout << ans[i][0];
        for (int j=1; j<n; ++j) cout << ' ' << ans[i][j];
        cout << endl;
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n>>k && n) solve();
}