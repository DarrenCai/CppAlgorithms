/**
 * UVa11542
 * 乘积是平方数
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 95
#define N 102
int prim[M] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83,
                89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
                181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277,
                281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389,
                397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499 };
int a[N][N], m, n;

int rnk() {
    int r = 0, c = 0;
    while (r<m && c<n) {
        int i = r;
        if (!a[i][c]) for (int j=i+1; j<m; ++j) if (a[j][c]) {
            i = j; break;
        }
        if (!a[i][c]) {
            if (++c == n) return r;
            continue;
        }
        if (i > r) for (int j=0, t; j<n; ++j) t = a[r][j], a[r][j] = a[i][j], a[i][j] = t;
        for (int j=(i=r++)+1; j<m; ++j) if (a[j][c]) for (int k=c; k<n; ++k) a[j][k] ^= a[i][k];
    }
    return r;
}

void solve() {
    cin >> n;
    memset(a, 0, sizeof(a));
    for (int i=m=0; i<n; ++i) {
        long long x; cin >> x;
        for (int j=0; prim[j]<=x; ++j) if (x%prim[j] == 0) {
            do {
                a[j][i] ^= 1; x /= prim[j];
            } while (x%prim[j] == 0) ;
            m = max(m, j+1);
            if (x == 1) break;
        }
    }
    cout << (1ll << (n - rnk())) - 1 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}