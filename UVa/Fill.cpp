/**
 * UVa10603
 * 倒水问题
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define N 202
int f[3][2][N], c[3], v[3], d, ans, p; bool inq[3][2][N];
struct node {
    int s, f, w;
    void decode() {
        int x = s<2 ? s+1 : 0;
        v[s] = f ? c[s] : 0; v[x] = w; v[3-s-x] = c[2] - v[s] - v[x];
    }
};

void solve() {
    cin >> c[0] >> c[1] >> c[2] >> d;
    ans = c[2] <= d ? c[2] : 0; p = 0;
    if (c[2] != d) {
        memset(f, -1, sizeof(f)); memset(inq, 0, sizeof(inq));
        queue<node> q; f[2][1][0] = 0; q.push({2, 1, 0});
        while (!q.empty()) {
            node t = q.front(); int &r = f[t.s][t.f][t.w]; t.decode(); q.pop(); inq[t.s][t.f][t.w] = false;
            for (int i=0; i<3; ++i) if (v[i]) for (int j=0; j<3; ++j) if (i != j) {
                int g, x, y, w[] = {v[0], v[1], v[2]};
                if (v[i] + v[j] > c[j]) g = r + c[j]-v[j], w[i] -= c[j]-v[j], w[j] = c[j], x = j, y = 1;
                else g = r + v[i], w[j] += v[i], w[i] = 0, x = i, y = 0;
                int z = w[x<2 ? x+1 : 0], &e = f[x][y][z];
                if (e < 0 || g < e) {
                    e = g;
                    for (int k=0; k<3; ++k) if (w[k]<=d && (w[k] > ans || (w[k]==ans && g<p))) ans = w[k], p = g;
                    if (!inq[x][y][z]) q.push({x, y, z}), inq[x][y][z] = true;
                }
            }
        }
    }
    cout << p << ' ' << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}