/**
 * UVa10537
 * 过路费（加强版）
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define N 128
int g[N][N], c[N], f[N], p[N], n, kase = 0; char s, t; long long d[N], w;
struct node {
    long long d; char u;
    bool operator< (const node& rhs) const {
        return d>rhs.d;
    }
};

void solve() {
    memset(c, 0, sizeof(c));
    while (n--) cin >> s >> t, g[s][c[s]++] = t, g[t][c[t]++] = s;
    cin >> w >> s >> t; p[t] = t;
    memset(d, 10, sizeof(d)); memset(f, 0, sizeof(f)); priority_queue<node> q; q.push({d[t] = w, t});
    while (!q.empty()) {
        char u = q.top().u; q.pop();
        if (u == s) break;
        if (f[u]) continue;
        f[u] = 1;
        for (int i=0; i<c[u]; ++i) {
            char v = g[u][i]; long long d1 = d[u] + (u>='a' ? 1 : (d[u]+18)/19);
            if (d[v] > d1 || (d[v] == d1 && p[v] > u)) d[v] = d1, p[v] = u, q.push({d[v], v});
        }
    }
    cout << "Case " << ++kase << ':' << endl << d[s] << endl;
    for (char u=s; u!=t; u=p[u]) cout << u << '-';
    cout << t << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n >= 0) solve();
    return 0;
}