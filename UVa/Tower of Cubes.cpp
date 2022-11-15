/**
 * UVa10051
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 101
#define N 505
int d[N][M], r[N][M], f[N][M], k[N][M], c[6], t[] = {1, 0, 3, 2, 5, 4}, n, kase = 0;
char s[][8] = {" front", " back", " left", " right", " top", " bottom"};

void print(int i, int c) {
    if (i>1 && d[i][c]==d[i-1][c]) return print(i-1, c);
    if (r[i][c]) print(r[i][c], k[i][c]);
    cout << i << s[f[i][c]] << endl;
}

void solve() {
    memset(d[1], 0, sizeof(d[1]));
    memset(r[1], 0, sizeof(r[1]));
    for (int i=0; i<6; ++i) cin >> c[i];
    for (int i=0; i<6; ++i) d[1][c[i]] = 1, f[1][c[i]] = t[i];
    for (int i=2; i<=n; ++i) {
        memcpy(d[i], d[i-1], sizeof(d[i]));
        memcpy(r[i], r[i-1], sizeof(r[i]));
        memcpy(f[i], f[i-1], sizeof(f[i]));
        memcpy(k[i], k[i-1], sizeof(k[i]));
        for (int j=0; j<6; ++j) cin >> c[j];
        for (int j=0, v; j<6; ++j) if ((v = d[i-1][c[t[j]]]+1) > d[i][c[j]])
            d[i][c[j]] = v, r[i][c[j]] = d[i][c[j]]>1 ? i-1 : 0, f[i][c[j]] = t[j], k[i][c[j]] = c[t[j]];
    }
    int ans = 0, x;
    for (int i=1; i<M; ++i) if (d[n][i] > ans) ans = d[n][i], x = i;
    if (kase++) cout << endl;
    cout << "Case #" << kase << endl << ans << endl;
    print(n, x);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) solve();
    return 0;
}