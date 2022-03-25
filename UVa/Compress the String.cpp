/**
 * UVa1491/LA5693
 * 字符串压缩
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 510
#define N 4
char s[M]; short a[N-1][N], b[N*N*N], l[N], ll[N], c[N], f[N], ff[N], m, n, t, cc;

void expand(short i = 0) {
    for (short j=0; j<ll[i]; ++j) {
        if (a[i][j]) {
            short k = a[i][j];
            if (f[k] < 0) f[k] = t;
            if (k == n-1) {
                b[t++] = 1; ++cc;
            } else expand(k);
        } else b[t++] = 0;
    }
}

bool check(short i, short l) {
    for (short j=0; j<ll[i]; ++j) {
        if (a[i][j]) {
            short k = a[i][j], tt = t;
            if (k == n-1) t += l;
            else if (!check(k, l)) return false;
            for (short p=tt; p<t; ++p) if (s[p] != s[p+ff[k]-tt]) return false;
        } else ++t;
    }
    return true;
}

bool check(short l) {
    for (short i=0, j=0; i<t; ++i) {
        for (short k=1; k<n; ++k) if (f[k] == i) ff[k] = j;
        b[i] ? j += l : ++j;
    }
    t = 0;
    return check(0, l);
}

bool dfs(short i = 0, short p = 0) {
    if (i == n-1) {
        for (short i=1; i<n; ++i) f[i] = -1;
        t = cc = 0;
        expand();
        for (short ll=2; ll<=l[i]; ++ll) if (t+cc*(ll-1) == m && check(ll)) return true;
        return false;
    }
    if (i>0 && (!c[i] || ll[i])) return dfs(i+1);
    for (short j=i; j<n; ++j) {
        ++c[a[i][p] = j==i ? 0 : j];
        if (p+1<l[i] && dfs(i, p+1)) return true;
        if (i == 0) for (short k=1; k<n; ++k) ll[k] = 0;
        ll[i] = p+1;
        if (dfs(i+1)) return true;
        --c[a[i][p]];
    }
    return false;
}

bool solve() {
    t = 1;
    for (short i=0; i<n; ++i) {
        cin >> l[i]; t *= l[i];
        if (l[i] == 1) --i, --n;
    }
    cin >> s;
    m = strlen(s);
    if (m > t) return false;
    if (n < 2) return true;
    for (short i=0; i<n; ++i) if (m <= l[i]) return true;
    for (short i=1; i<n; ++i) c[i] = 0;
    return dfs();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) cout << (solve() ? "Yes" : "No") << endl;
    return 0;
}
