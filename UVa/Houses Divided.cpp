/**
 * LA2108
 * Regionals 2000 >> North America - Mid-Atlantic USA
 * 暂时无法提交,感觉会超时
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 12
#define M 25
char names[M][N], s[N];
short a[M], h[M], d[M][M], ss[M][M], p[M][2], q[1000000][M][2], kase = 0, m, n, r, t; int c; bool vis[N][N];

short find() {
    for (short i=0; i<t; ++i) if (strcmp(names[i], s) == 0) return i;
    memcpy(names[t], s, sizeof(s));
    return t++;
}

bool check(short i, short x, short y) {
    if (vis[x][y]) return false;
    for (short j=0; j<i; ++j) if (d[a[i]][a[j]] && abs(x-p[a[j]][0]) + abs(y-p[a[j]][1]) != d[a[i]][a[j]]) return false;
    return true;
}

void dfs(short i = 0) {
    if (i == t) {
        memcpy(q[c++], p, sizeof(p));
        return;
    }
    if (p[a[i]][0] > -1) return dfs(i+1);
    for (short x=0; x<m; ++x) for (short y=0; y<n; ++y) if (check(i, x, y)) {
        vis[x][y] = true;
        p[a[i]][0] = x; p[a[i]][1] = y;
        dfs(i+1);
        p[a[i]][0] = -1;
        vis[x][y] = false;
    }
}

void ans() {
    short a = M, b = 0; memset(ss, 10, sizeof(ss));
    for (int i=0; i<c; ++i) {
        short mx = 0;
        for (short j=0; j<r; ++j) for (short k=j+1; k<r; ++k) {
            short v = abs(q[i][h[j]][0]-q[i][h[k]][0]) + abs(q[i][h[j]][1]-q[i][h[k]][1]);
            mx = max(mx, v);
            ss[j][k] = min(ss[j][k], v);
        }
        a = min(a, mx);
    }
    for (short j=0; j<r; ++j) for (short k=j+1; k<r; ++k) b = max(b, ss[j][k]);
    if (kase++) cout << endl;
    cout << "DESCRIPTION " << kase << endl;
    cout << "Maximum guaranteed separation is " << a << " blocks." << endl;
    cout << "Houses separated by at least " << b << " blocks:" << endl;
    for (short j=0; j<r; ++j) for (short k=j+1; k<r; ++k)
        if (ss[j][k] == b) cout << names[h[j]] << ' ' << names[h[k]] << endl;
}

void solve() {
    memset(vis, 0, sizeof(vis)); memset(d, r = t = 0, sizeof(d)); memset(p, -1, sizeof(p));
    while (cin >> s) {
        if (strcmp(s, "END") == 0) break;
        short k = find();
        if (strncmp(s, "house", 5) == 0) h[r++] = k;
        cin >> s;
        if (s[0] == 'L') {
            cin >> s[0] >> p[k][1];
            p[k][0] = s[0] - 'A';
            vis[p[k][0]][p[k][1]] = true;
        } else {
            short dd; cin >> dd >> s;
            d[k][find()] = dd;
        }
    }
    for (short i=c=0; i<t; ++i) if (p[i][0] > -1) a[c++] = i;
    for (short i=0; i<t; ++i) if (p[i][0] < 0) a[c++] = i;
    c = 0;
    dfs();
    ans();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>m>>n && m) solve();
    return 0;
}