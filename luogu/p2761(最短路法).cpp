/**
 * p2761 软件补丁问题
 * 同UVa658 It’s not a Bug, it’s a Feature!
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define T 22
#define M 110
#define N 1050000
int cnt[N], c[M], d[N], m, n, cc; char s1[M][T], s2[M][T], s[N][T]; struct {int v, c;} g[N][M];
struct node {int u, d; node(int u, int d):u(u),d(d){}}; vector<node> q; map<string, int> id;

void build(int u) {
    cnt[u] = 0;
    for (int i=0; i<m; ++i) {
        bool ok = true;
        for (int j=0; j<n; ++j) if ((s1[i][j]=='+' && s[u][j]!='+') || (s1[i][j]=='-' && s[u][j]!='-')) {
            ok = false; break;
        }
        if (ok) {
            int v = id.size(); char (&r)[T] = s[v]; r[n] = 0;
            for (int j=0; j<n; ++j) r[j] = s2[i][j]=='0' ? s[u][j] : s2[i][j];
            string ss(r); bool f = false;
            if (!id.count(ss)) id[ss] = v, f = true;
            if ((v = id[ss]) > 0 && v != u) {
                g[u][cnt[u]].v = v; g[u][cnt[u]++].c = c[i];
                if (f) {
                    d[v] = d[u] + c[i];
                    q.push_back(node(v, d[v])); build(v);
                } else if (d[v]==0 || d[v] > d[u] + c[i]) {
                    d[v] = d[u] + c[i];
                    if (v == 1) cc = d[v];
                    else q.push_back(node(v, d[v]));
                }
            }
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) {
        id.clear(); q.clear(); cc = 0; s[0][n] = s[1][n] = 0;
        for (int i=0; i<m; ++i) cin >> c[i] >> s1[i] >> s2[i];
        for (int i=0; i<n; ++i) s[0][i] = '+'; id[string(s[0])] = 0;
        for (int i=0; i<n; ++i) s[1][i] = '-'; id[string(s[1])] = 1;
        build(d[0] = d[1] = 0);
        for (int i=0; i<q.size(); ++i) {
            int u = q[i].u, dd = q[i].d;
            if (dd == d[u]) for (int j=0; j<cnt[u]; ++j) {
                int v = g[u][j].v, c = g[u][j].c + d[u];
                if (d[v] > c) {
                    d[v] = c;
                    if (v == 1) cc = d[v];
                    else q.push_back(node(v, d[v]));
                }
            }
        }
        cout << cc << endl;
    }
    return 0;
}