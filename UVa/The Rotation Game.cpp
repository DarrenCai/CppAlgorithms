/**
 * UVa1343/LA3265
 * 旋转游戏
 * Shanghai 2004
 */

#include <iostream>
using namespace std;

#define M 16
const int m = 8, n = 24, c[] = {6, 7, 8, 11, 12, 15, 16, 17}, f[] = {5, 4, 7, 6, 1, 0, 3, 2},
        idx[][7] = {{0, 2, 6, 11, 15, 20, 22}, {1, 3, 8, 12, 17, 21, 23},
                    {10, 9, 8, 7, 6, 5, 4}, {19, 18, 17, 16, 15, 14, 13},
                    {23, 21, 17, 12, 8, 3, 1}, {22, 20, 15, 11, 6, 2, 0},
                    {13, 14, 15, 16, 17, 18, 19}, {4, 5, 6, 7, 8, 9, 10}};
int v[n]; char a[M+1];

int h() {
    int cnt[] = {0, 0, 0, 0}, mx = 0;
    for (int j=0; j<m; ++j) mx = max(mx, ++cnt[v[c[j]]]);
    return m - mx;
}

bool IDAStar(int s, int d) {
    if (s == d) {
        for (int i=1; i<m; ++i) if (v[c[i]] != v[c[i-1]]) return false;
        return true;
    } else for (int i=0; i<m; ++i) if (s == 0 || f[i] != a[s-1]-'A') {
        int x = v[idx[i][0]];
        for (int j=1, k=m-1; j<k; ++j) v[idx[i][j-1]] = v[idx[i][j]];
        v[idx[i][m-2]] = x; a[s] = 'A'+i;
        if (s+h() < d && IDAStar(s+1, d)) return true;
        x = v[idx[i][m-2]];
        for (int j=m-2; j>0; --j) v[idx[i][j]] = v[idx[i][j-1]];
        v[idx[i][0]] = x;
    }
    return false;
}

void solve() {
    for (int i=1; i<n; ++i) cin >> v[i];
    for (int d=0; d<M; a[++d] = 0) if (IDAStar(0, d)) {
        cout << (d == 0 ? "No moves needed" : a) << endl << v[c[0]] << endl;
        break;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> v[0] && v[0]) solve();
    return 0;
}