/**
 * UVa820
 * 因特网带宽
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 125
#define M 32000
#define INF 11000

struct edge {short u, v, cap, flow;} e[M];
short g[N][M], q[N*M], p[N], a[N], cnt[N], n, c;

void addEdge(short u, short v, short cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short kase = 0;
    while (cin>>n && n) {
        short s, t, cc; cin >> s >> t >> cc;
        memset(cnt, c = 0, sizeof(cnt));
        while (cc--) {
            short u, v, b; cin >> u >> v >> b;
            addEdge(u, v, b); addEdge(v, u, b); 
        }
        int flow = 0;
        while (true) {
            memset(a, 0, sizeof(a)); a[s] = INF; q[0] = s;
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
            if (!a[t]) break;
            flow += a[t];
            for (short u=t; u!=s; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        cout << "Network " << ++kase << endl << "The bandwidth is " << flow << '.' << endl << endl;
    }
    return 0;
}