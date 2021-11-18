/**
 * UVa1660
 * 电视网络
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 110
struct edge {short u, v, cap, flow;} e[N*N>>1];
short u[N*N>>3], v[N*N>>3], g[N][N>>1], q[N*N*N>>1], p[N], a[N], cnt[N], n, m, c;

void addEdge(short u, short v, short cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

short maxFlow(short s, short t) {
    memset(cnt, c = 0, sizeof(cnt));
    for (short i=0; i<n; ++i) addEdge(i, i+n, 1);
    // 理解一下这几行
    // for (short i=0; i<m; ++i) {
    //     addEdge(u[i]+n, v[i], u[i]+n==s && v[i]==t ? N : 1);
    //     addEdge(v[i]+n, u[i], v[i]+n==s && u[i]==t ? N : 1);
    // }
    for (short i=0; i<m; ++i) addEdge(u[i]+n, v[i], N), addEdge(v[i]+n, u[i], N);
    short flow = 0;
    while (true) {
        memset(a, 0, sizeof(a)); a[s] = N; q[0] = s;
        int head = 0, tail = 1;
        while (head < tail) {
            short u = q[head++];
            for (short i=0; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]];
                if (!a[ee.v] && ee.cap > ee.flow) {
                    p[ee.v] = g[u][i];
                    a[ee.v] = min(a[u], short(ee.cap-ee.flow));
                    q[tail++] = ee.v;
                }
            }
            if (a[t]) break;
        }
        if (!a[t]) return flow;
        flow += a[t];
        for (short u=t; u!=s; u=e[p[u]].u) {
            e[p[u]].flow += a[t];
            e[p[u]^1].flow -= a[t];
        }
    }
    return flow;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) {
        short ans = n; char t;
        for (short i=0; i<m; ++i) cin >> t >> u[i] >> t >> v[i] >> t;
        for (short i=0; i<n; ++i) for (short j=i+1; j<n; ++j) ans = min(ans, maxFlow(j+n, i));
        cout << ans << endl;
    }
}