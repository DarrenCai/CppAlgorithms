/**
 * p2774 方格取数问题
 */

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define N 10100
#define INF 100100
struct edge {int u, v, cap, flow;} e[10*N];
int g[N][N>>1], a[N], p[N], cnt[N], m, n, c;

void addEdge(int u, int v, int cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> m >> n) {
        memset(cnt, c = 0, sizeof(cnt));
        int t = m*n+1, v, ans = 0;
        for (int i=0; i<m; ++i) for (int j=1; j<=n; ++j) {
            cin >> v; ans += v; int u = i*n+j;
            if ((i&1 && j&1) || (~i&1 && ~j&1)) {
                addEdge(0, u, v);
                if (u-n > 0) addEdge(u, u-n, INF);
                if (u+n < t) addEdge(u, u+n, INF);
                if (j > 1) addEdge(u, u-1, INF);
                if (j < n) addEdge(u, u+1, INF);
            } else addEdge(u, t, v);
        }
        while (true) {
            vector<int> q; q.push_back(0);
            memset(a, 0, sizeof(a)); a[0] = INF;
            int head = 0, tail = 1;
            while (head < tail) {
                int u = q[head++];
                for (int i=0; i<cnt[u]; ++i) {
                    const edge& ee = e[g[u][i]];
                    if (!a[ee.v] && ee.cap > ee.flow) {
                        p[ee.v] = g[u][i];
                        a[ee.v] = min(a[u], ee.cap-ee.flow);
                        q.push_back(ee.v); tail++;
                    }
                }
                if (a[t]) break;
            }
            if (!a[t]) break;
            ans -= a[t];
            for (int u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        cout << ans << endl;
    }
    return 0;
}