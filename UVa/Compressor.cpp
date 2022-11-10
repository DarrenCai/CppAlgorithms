/**
 * UVa11521
 * 压缩
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 205
char s[N]; int d[N][N], b[N][N], f[N][N][N], x[N][N][N], y[N][N][N], n; bool e[N][N][N];

void print(int i, int j) {
    int l = b[i][j];
    if (l < 0) {
        for (int k=i; k<=j; ++k) cout << s[k];
        return;
    }
    if (l < j) {
        print(i, l);
        return print(l+1, j);
    }
    l >>= 9;
    cout << '['; print(i, i+l-1); cout << ']'; cout << x[l][i][j];
    int k = y[l][i][j] ? y[l][i][j] : j-l+1, c = 1;
    if (i+l < k) cout << '{', print(i+l, k-1), cout << "}" << c;
    while (y[l][k][j]) {
        ++c;
        if (k+l < y[l][k][j]) cout << '{', print(k+l, y[l][k][j]-1), cout << '}' << c;
        k = y[l][k][j];
    }
    if (k+l <= j-l) cout << '{', print(k+l, j-l), cout << "}" << ++c;
}

void solve() {
    n = strlen(s);
    for (int l=1; l<=n; ++l) for (int i=0, ii=n-l, j; i<=ii; ++i) {
        int &r = d[i][j = i+l-1] = l; b[i][j] = -1;
        for (int k=i-l; k>=0; --k) e[l][k][i] = s[k]==s[i] && (l==1 || e[l-1][k+1][i+1]);
        for (int k=i, ll; k<j; ++k) {
            int v = d[i][k] + d[k+1][j];
            if (v < r) r = v, b[i][j] = k;
            if (2*(ll = k-i+1) <= l && e[ll][i][j-ll+1]) {
                int c = d[i][k] + 3, &s = f[ll][i][j] = c + ((ll<<1) < l ? d[k+1][j-ll]+3 : 0);
                x[ll][i][j] = 2; y[ll][i][j] = 0;
                for (int p=k+1, t=j-ll-ll+1; p<=t; ++p) if (e[ll][i][p]) {
                    v = f[ll][i][p+ll-1] + f[ll][p][j] - c;
                    if (v < s) s = v, x[ll][i][j] = x[ll][i][p+ll-1] + x[ll][p][j] - 1, y[ll][i][j] = p;
                }
                if (s < r) r = s, b[i][j] = ll << 9;
            }
        }
    }
    cout << d[0][n-1] << ' ';
    print(0, n-1);
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> s) solve();
    return 0;
}