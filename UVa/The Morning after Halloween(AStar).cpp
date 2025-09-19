/**
 * UVa1601/LA3888
 * 万圣节后的早晨
 * Tokyo 2007
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define N 16
int g[1<<24], x[26], y[26], p[3], t[3], a[3], e, w, h, n, ans; bool f[N][N]; vector<int> d[N*N];

struct node {
    int d, s, v;
    bool operator< (const node& rhs) const {
        return d > rhs.d;
    }
};

int hh() {
    int x = 0;
    for (int i=0; i<n; ++i) x = max(x, abs((p[i]>>4) - (t[i]>>4)) + abs((p[i]&15) - (t[i]&15)));
    return x;
}

int AStar() {
    node t = {hh(), 0, n<2 ? p[0] : (n<3 ? p[1]<<8 | p[0] : p[2]<<16 | p[1]<<8 | p[0])};
    priority_queue<node> q; q.push(t); memset(g, 0x7f, sizeof(g)); g[t.v] = 0;
    while (!q.empty()) {
        t = q.top(); q.pop();
        if (t.s++ > g[t.v]) continue;
        for (int v=t.v, i=0; i<n; ++i, v>>=8) a[i] = v&255;
        for (int u=a[0], i=d[u].size()-1; i>=0; --i) {
            p[0] = d[u][i];
            if (n == 1) {
                if (p[0] == e) return t.s;
                if (t.s < g[p[0]]) q.push({t.s+hh(), g[p[0]] = t.s, p[0]});
            } else for (int v=a[1], j=d[v].size()-1; j>=0; --j) {
                p[1] = d[v][j];
                if (p[0] == p[1] || (p[0] == a[1] && p[1] == a[0])) continue;
                if (n == 2) {
                    int ss = p[1]<<8 | p[0];
                    if (ss == e) return t.s;
                    if (t.s < g[ss]) q.push({t.s+hh(), g[ss] = t.s, ss});
                } else for (int w=a[2], k=d[w].size()-1; k>=0; --k) {
                    p[2] = d[w][k];
                    if (p[0] == p[2] || p[1] == p[2] || (p[0] == a[2] && p[2] == a[0]) ||
                        (p[1] == a[2] && p[2] == a[1])) continue;
                    int ss = p[2]<<16 | p[1]<<8 | p[0];
                    if (ss == e) return t.s;
                    if (t.s < g[ss]) q.push({t.s+hh(), g[ss] = t.s, ss});
                }
            }
        }
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
    for (int i=e=0; i<h; ++i) for (int j=0; j<w; ++j) if (!f[i][j]) {
        int u = i<<4 | j; d[u].clear(); d[u].push_back(u);
        if (i && !f[i-1][j]) d[u].push_back(u-16);
        if (i+1 < h && !f[i+1][j]) d[u].push_back(u+16);
        if (j && !f[i][j-1]) d[u].push_back(u-1);
        if (j+1 < w && !f[i][j+1]) d[u].push_back(u+1);
    }
    for (int i=n-1; i>=0; --i) p[i] = x[a[i]], t[i] = y[a[i]], e = e<<8 | t[i];
    cout << AStar() << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> w >> h >> n && w) solve();
    return 0;
}