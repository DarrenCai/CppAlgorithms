/**
 * UVa12163/LA4411
 * 加减游戏
 * Kuala Lumpur 2008
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 15
#define V 102

int b[1<<N]={0}, s[1<<N]={0}, f[1<<N], k[V], sg[V], e[V][N], c[V];

void calcSG(int i) {
    if (sg[i] >= 0) return;
    int m = 1<<c[i], &r = sg[i] = 0;
    if (c[i]==0) return;
    for (int j=0; j<c[i]; ++j) calcSG(e[i][j]);
    for (int j=0; j<c[i]; ++j) s[1<<j] = sg[e[i][j]];
    for (int x=3; x<m; ++x) s[x] = s[x&(-x)]^s[x&(x-1)];
    for (int x=0; x<m; ++x) if (b[x]<=k[i] && (b[x]&1)==(k[i]&1)) f[s[x]] = i;
    while (f[r] == i) ++r;
}

void solve() {
    memset(c, 0, sizeof(c));
    memset(f, -1, sizeof(f));
    memset(sg, -1, sizeof(sg));
    int m, n; cin >> m >> n;
    while (n--) {
        int f, t; cin >> f >> t;
        e[f][c[f]++] = t;
    }
    for (int i=0; i<m; ++i) cin >> k[i];
    for (int i=0; i<m; ++i) calcSG(i);
    int r; cin >> r;
    for (int i=1, s; i<=r; ++i) {
        for (int j=s=0; j<m; ++j) {
            int v; cin >> v;
            if (v & 1) s ^= sg[j];
        }
        cout << "Round#" << i << ": " << (s ? "WINNING" : "LOSING") << endl;
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    for (int i=0; i<N; ++i) b[1<<i] = 1;
    for (int i=3, j=1<<N; i<j; ++i) b[i] = b[i&(-i)] + b[i&(i-1)];
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Game#" << kase << ":" << endl, solve();
    return 0;
}