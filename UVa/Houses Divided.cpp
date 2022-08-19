/**
 * UVa1295/LA2108
 * Regionals 2000 >> North America - Mid-Atlantic USA
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 12
#define M 25
char names[M][N], s[N]; short h[M], d[M][M], ss[M][M], p[M][2], kase = 0, m, n, a, r, t; bool vis[N][N];

short find() {
    for (short i=0; i<t; ++i) if (strcmp(names[i], s) == 0) return i;
    return -1;
}

bool check(short i, short x, short y) {
    if (vis[x][y]) return false;
    for (short j=0; j<i; ++j) if (d[i][j] && abs(x-p[j][0]) + abs(y-p[j][1]) != d[i][j]) return false;
    return true;
}

void dfs(short i = 0) {
    if (i == t) {
        short mx = 0;
        for (short j=0; j<r; ++j) for (short k=j+1; k<r; ++k) {
            short d = abs(p[h[j]][0]-p[h[k]][0]) + abs(p[h[j]][1]-p[h[k]][1]);
            mx = max(mx, d);
            ss[j][k] = min(ss[j][k], d);
        }
        a = min(a, mx);
        return;
    }
    if (p[i][0] > -1) return dfs(i+1);
    for (short x=0; x<m; ++x) for (short y=0; y<n; ++y) if (check(i, x, y)) {
        vis[x][y] = true;
        p[i][0] = x; p[i][1] = y;
        dfs(i+1);
        p[i][0] = -1;
        vis[x][y] = false;
    }
}

void ans() {
    short b = 0;
    for (short i=0; i<r; ++i) for (short j=i+1; j<r; ++j) b = max(b, ss[i][j]);
    cout << "DESCRIPTION " << ++kase << endl;
    cout << "Maximum guaranteed separation is " << a << " blocks." << endl;
    cout << "Houses separated by at least " << b << " blocks:" << endl;
    for (short i=0; i<r; ++i) for (short j=i+1; j<r; ++j)
        if (ss[i][j] == b) cout << names[h[i]] << ' ' << names[h[j]] << endl;
    cout << endl;
}

void solve() {
    memset(d, r=t=0, sizeof(d)); memset(ss, 10, sizeof(ss)); memset(p, -1, sizeof(p)); memset(vis, 0, sizeof(vis));
    while (cin>>s) {
        if (strcmp(s, "END") == 0) break;
        short k = find();
        if (k < 0) {
            memcpy(names[k=t++], s, sizeof(s));
            if (strncmp(s, "house", 5) == 0) h[r++] = k;
        }
        cin >> s;
        if (s[0]=='L') {
            cin >> s[0] >> p[k][1];
            p[k][0] = s[0]-'A';
            vis[p[k][0]][p[k][1]] = true;
        } else {
            short dd; cin >> dd >> s;
            d[k][find()] = dd;
        }
    }
    a = M;
    dfs();
    ans();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>m>>n && m) solve();
    return 0;
}