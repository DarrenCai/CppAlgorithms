/**
 * LA5304/UVa387
 * Regionals 1995 >> North America - Mid-Central USA
 */

#include <iostream>
using namespace std;

#define M 6
#define N 4
char p[M][N][N]; short ans[N][N], w[M], h[M], x[M], n, kase=0; bool vis[M];

bool check(short x0, short y0, short i) {
    if (y0+w[i]>N || x0+h[i]-x[i]>N || x0<x[i]) return false;
    for (short r=0; r<h[i]; ++r) for (short c=0; c<w[i]; ++c) if (p[i][r][c]=='1') {
        short u = x0+r-x[i], v = y0+c;
        if (ans[u][v]) return false;
    }
    return true;
}

void fill(short x0, short y0, short i) {
    for (short r=0; r<h[i]; ++r) for (short c=0; c<w[i]; ++c) if (p[i][r][c]=='1') ans[x0+r-x[i]][y0+c] = i+1;
}

void unfill(short x0, short y0, short i) {
    for (short r=0; r<h[i]; ++r) for (short c=0; c<w[i]; ++c) if (p[i][r][c]=='1') ans[x0+r-x[i]][y0+c] = 0;
}

bool dfs() {
    bool found = false; short x0, y0;
    for (short j=0; j<N; ++j) {
        for (short i=0; i<N; ++i) if (!ans[i][j]) {
            x0 = i; y0 = j; found = true;
            break;
        }
        if (found) break;
    }
    if (!found) {
        for (short i=0; i<n; ++i) if (!vis[i]) return false;
        return true;
    }
    for (short i=0; i<n; ++i) if (!vis[i] && check(x0, y0, i)) {
        vis[i] = true; fill(x0, y0, i);
        if (dfs()) return true;
        vis[i] = false; unfill(x0, y0, i);
    }
    return false;
}

void solve() {
    for (short i=0; i<n; ++i) {
        x[i] = N; vis[i] = false;
        cin >> h[i] >> w[i];
        for (short j=0; j<h[i]; ++j) for (short k=0; k<w[i]; ++k) {
            cin >> p[i][j][k];
            if (k==0 && p[i][j][k]=='1') x[i] = min(x[i], j);
        }
    }
    for (short i=0; i<N; ++i) for (short j=0; j<N; ++j) ans[i][j] = 0;
    if (kase++) cout << endl;
    if (dfs()) {
        for (short i=0; i<N; ++i) {
            for (short j=0; j<N; ++j) cout << ans[i][j];
            cout << endl;
        }
    } else cout << "No solution possible" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) solve();
    return 0;
}