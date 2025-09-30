/**
 * UVa1499/LA5722
 * Beijing 2011
 */

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define N 8
int v[N][N], c[N], m, n, k, ans; bool vis[N][N];

void dfs(const int (&v)[N][N], int m, int n, int i, int j, vector<int>& out) {
    vis[i][j] = true; out.push_back(i<<3 | j);
    for (int x=i-1, k=i+2, t=j+2; x<k; ++x) if (x >= 0 && x < n) for (int y=j-1; y<t; ++y)
        if (y >= 0 && y < m && !vis[x][y] && v[x][y] == v[i][j]) dfs(v, m, n, x, y, out);
}

void find_cc(const int (&v)[N][N], int m, int n, vector<vector<int> >& out) {
    memset(vis, 0, sizeof(vis));
    for (int i=0; i<n; ++i) for (int j=0; j<m; ++j) if (v[i][j] && !vis[i][j]) {
        vector<int> c; dfs(v, m, n, i, j, c);
        if (c.size() > 2) out.push_back(c);
    }
}

void upd(int (&v)[N][N], int &m, int &n) {
    int t = 0;
    for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) if (v[j][i]) {
        c[t++] = i;
        break;
    }
    for (m=0; m<t; ++m) for (int j=0; j<n; ++j) v[j][m] = v[j][c[m]];
    for (int i=t=0; i<m; t = max(t, n-c[i++])) {
        for (int j = (c[i]=n) - 1; j>=0; --j) if (v[j][i]) v[--c[i]][i] = v[j][i];
        for (int j=0; j<c[i]; ++j) v[j][i] = 0;
    }
    for (int i=0, k=n-t; i<m; ++i) for (int j=0; j<t; ++j) v[j][i] = v[j+k][i];
    n = t;
}

int h(const int (&v)[N][N], int m, int n) {
    int s = 0;
    for (int i=1; i<=k; ++i) c[i] = 0;
    for (int i=0; i<n; ++i) for (int j=0; j<m; ++j) if (v[i][j]) ++c[v[i][j]];
    for (int i=1; i<=k; ++i) if (c[i] > 2) s += c[i]*c[i];
    return s;
}

void AStar(const int (&v)[N][N], int m, int n, int p = 0) {
    if (p + h(v, m, n) <= ans) return;
    vector<vector<int> > c; find_cc(v, m, n, c);
    if (c.size() > 0) {
        for (int i=c.size()-1; i>=0; --i) {
            int w[N][N], m1 = m, n1 = n, t = c[i].size(); memcpy(w, v, sizeof(v));
            for (int j=0; j<t; ++j) w[c[i][j] >> 3][c[i][j] & 7] = 0;
            upd(w, m1, n1); AStar(w, m1, n1, p + t*t);
        }
    } else ans = max(ans, p);
}

void solve() {
    for (int i=ans=0; i<n; ++i) for (int j=0; j<m; ++j) cin >> v[i][j];
    AStar(v, m, n);
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m >> k) solve();
    return 0;
}