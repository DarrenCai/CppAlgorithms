/**
 * UVa1601/LA3888
 * 万圣节后的早晨
 * Tokyo 2007
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 16
int q[1<<24], x[26], y[26], p[3], t[3], a[3], d[] = {1, 0, 0, -1, 0}, e[] = {0, -1, 1, 0, 0}, w, h, n, ans;
bool f[N][N], vis[1<<24];

bool check() {
    for (int i=0; i<n; ++i) if (p[i] != t[i]) return false;
    return true;
}

int bfs() {
    memset(vis, 0, sizeof(vis)); vis[q[0] = n<2 ? p[0] : (n<3 ? p[1]<<8 | p[0] : p[2]<<16 | p[1]<<8 | p[0])] = true;
    for (int s=1, c=1, t=1, r=0; r<c;) {
        for (int v=q[r], i=0; i<n; ++i, v>>=8) a[i] = v&255, x[i] = a[i]>>4, y[i] = a[i]&15;
        for (int i=0, u, v; i<5; ++i) {
            u = x[0] + d[i]; v = y[0] + e[i]; p[0] = u<<4 | v;
            if (u < 0 || u >= h || v < 0 || v >= w || f[u][v]) continue;
            if (n == 1) {
                if (check()) return s;
                if (!vis[p[0]]) vis[p[0]] = true, q[t++] = p[0];
            } else for (int j=0; j<5; ++j) {
                u = x[1] + d[j]; v = y[1] + e[j]; p[1] = u<<4 | v;
                if (u < 0 || u >= h || v < 0 || v >= w || f[u][v] || p[0] == p[1] || (p[0] == a[1] && p[1] == a[0])) continue;
                if (n == 2) {
                    if (check()) return s;
                    int ss = p[1]<<8 | p[0];
                    if (!vis[ss]) vis[ss] = true, q[t++] = ss;
                } else for (int k=0; k<5; ++k) {
                    u = x[2] + d[k]; v = y[2] + e[k]; p[2] = u<<4 | v;
                    if (u < 0 || u >= h || v < 0 || v >= w || f[u][v] || p[0] == p[2] || p[1] == p[2] ||
                        (p[0] == a[2] && p[2] == a[0]) || (p[1] == a[2] && p[2] == a[1])) continue;
                    if (check()) return s;
                    int ss = p[2]<<16 | p[1]<<8 | p[0];
                    if (!vis[ss]) vis[ss] = true, q[t++] = ss;
                }
            }
        }
        if (++r == c) c = t, ++s;
    }
    return -1;
}

void solve() {
    for (int i=0, k=0; i<h; ++i) {
        cin.get();
        for (int j=0; j<w; ++j) {
            char c = cin.get();
            f[i][j] = c == '#';
            if (c >= 'a' && c <= 'z') x[a[k++] = c-'a'] = i<<4 | j;
            if (c >= 'A' && c <= 'Z') y[c-'A'] = i<<4 | j;
        }
    }
    for (int i=0; i<n; ++i) p[i] = x[a[i]], t[i] = y[a[i]];
    cout << bfs() << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> w >> h >> n && w) solve();
    return 0;
}