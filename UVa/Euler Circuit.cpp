/**
 * UVa10735
 * 混合图的欧拉回路
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 150
#define M 650
struct edge {short u, v, cap, flow;} e[2*M*N];
short q[2*M*N*(M+N)], cnt[M+N], a[M+N], path[M], u[M], v[M], d[N], cc, n, m;
int g[M+N][M], p[M+N], id[M], c; bool vis[N][M];

void addEdge(short u, short v, short cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

bool check() {
    for (short i=1; i<=n; ++i) if (d[i]&1) return false;
    return true;
}

void euler(short u) {
    for (short i=0; i<cnt[u]; ++i) if (!vis[u][i]) {
        vis[u][i] = true;
        euler(g[u][i]);
        path[cc++] = g[u][i];
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short tt; cin >> tt;
    while (tt--) {
        memset(d, 0, sizeof(d));
        memset(cnt, 0, sizeof(cnt));
        cin >> n >> m;
        short t = n+1; c = 0; cc = t;
        for (short i=0; i<m; ++i) {
            char c; cin >> u[i] >> v[i] >> c;
            ++d[u[i]]; --d[v[i]];
            if (c == 'U') {
                id[i] = ::c;
                addEdge(u[i], v[i], 1);
            } else id[i] = -1;
        }
        if (check()) {
            short s = 0, flow = 0;
            for (short i=1; i<=n; ++i) {
                if (d[i] > 0) addEdge(0, i, d[i]>>1), s += d[i]>>1;
                if (d[i] < 0) addEdge(i, t, -d[i]>>1);
            }
            while (true) {
                memset(a, 0, sizeof(a)); a[0] = m; q[0] = 0;
                int head = 0, tail = 1;
                while (head < tail) {
                    short u = q[head++];
                    for (short i=0; i<cnt[u]; ++i) {
                        const edge& ee = e[g[u][i]];
                        if (!a[ee.v] && ee.cap > ee.flow) {
                           p[ee.v] = g[u][i];
                           a[ee.v] = min(int(a[u]), ee.cap-ee.flow);
                           q[tail++] = ee.v; 
                        }
                    }
                    if (a[t]) break;
                }
                if (!a[t]) break;
                flow += a[t];
                for (short u=t; u!=0; u=e[p[u]].u) {
                    e[p[u]].flow += a[t];
                    e[p[u]^1].flow -= a[t];
                }
            }
            if (s != flow) {
                cout << "No euler circuit exist" << endl;
            } else {
                for (short i=0; i<m; ++i) if (id[i] >= 0) {
                    const edge& ee = e[id[i]];
                    if (ee.flow>0 && ee.u>0 && ee.v<t && ee.v>0 && ee.v<t) {
                        u[i] = u[i]+v[i]; v[i] = u[i]-v[i]; u[i] = u[i]-v[i];
                    }
                }
                memset(cnt, cc=0, sizeof(cnt));
                memset(vis, 0, sizeof(vis));
                for (short i=0; i<m; ++i) g[u[i]][cnt[u[i]]++] = v[i];
                cout << 1;
                euler(1);
                while (--cc >= 0) cout << ' ' << path[cc];
                cout << endl;
            }
        } else {
            cout << "No euler circuit exist" << endl;
        }
        if (tt) cout << endl;
    }
    return 0;
}