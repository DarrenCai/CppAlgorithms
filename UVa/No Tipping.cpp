/**
 * UVa10123
 */

#include <iostream>
using namespace std;

#define N 24
int p[1<<N], w[1<<N], w1[1<<N], w2[1<<N], fa[1<<N], q[1<<N], kase=0, m, b, n; bool vis[1<<N];

bool solve() {
    m = (1<<n)-1; w1[0] = w2[0] = 3*b;
    for (int i=0; i<n; ++i) cin >> p[1<<i] >> w[1<<i];
    for (int i=1; i<=m; ++i) {
        vis[i] = false;
        int j = i&(-i);
        w1[i] = w1[i^j] + (3+2*p[j])*w[j];
        w2[i] = w2[i^j] + (3-2*p[j])*w[j];
    }
    if (w1[m]<0 || w2[m]<0) return false;
    int head = 0, tail = 1; q[0] = 0;
    while (head < tail) {
        int u = q[head++];
        for (int i=1; i<m; i<<=1) {
            int v = u | i;
            if (vis[v]) continue;
            vis[v] = true;
            if (w1[v]>=0 && w2[v]>=0) {
                fa[v] = u; q[tail++] = v;
                if (v == m) return true;
            }
        }
    }
    return false;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>m>>b>>n && n) {
        cout << "Case " << ++kase << ':' << endl;
        if (solve()) for (int i=m; i>0; i=fa[i]) cout << p[i^fa[i]] << ' ' << w[i^fa[i]] << endl;
        else cout << "Impossible" << endl;
    }
    return 0;
}