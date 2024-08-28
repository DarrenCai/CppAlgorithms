/**
 * UVa1659/LA4030
 * 帮助小罗拉
 * Beijing 2007
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
using namespace std;

#define N 120
#define M 1780
struct edge {short u, v, cap, flow; double cost;} e[M];
double x[N], y[N], d[N], s, t, ans; short g0[N][N], cnt0[N], n;
short g[N][N], q[M*N], cnt[N], a[N], p[N], c; bool visit[N];

void addEdge(short u, short v, short cap, double cost) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cost; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cost; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(2);
    int kase = 0;
    while (cin>>n && n) {
        cin >> s >> t;
        memset(cnt0, 0, sizeof(cnt0));
        for (short i=1; i<=n; ++i) {
            cin >> x[i] >> y[i];
            short v; while (cin>>v && v) g0[i][cnt0[i]++] = v;
        }
        memset(a, 0, sizeof(a));
        memset(cnt, c=0, sizeof(cnt));
        ans = 0.;
        for (short u=1; u<=n; ++u) for (short i=0; i<cnt0[u]; ++i) {
            short v = g0[u][i]; double cc = t-s*sqrt(pow(x[u]-x[v],2)+pow(y[u]-y[v],2));
            if (cc < 0) {
                ans += cc;
                ++a[v];
                --a[u];
                addEdge(v, u, 1, -cc);
            } else addEdge(u, v, 1, cc);
        }
        for (short u=1; u<=n; ++u) if (a[u] != 0)
            a[u] > 0 ? addEdge(0, u, a[u], 0.) : addEdge(u, n+1, -a[u], 0.);
        while (true) {
            for (short i=0; i<n+2; ++i) d[i] = 1e39;
            memset(visit, 0, sizeof(visit));
            d[0] = 0.; q[0] = 0; p[0] = 0; a[0] = 1;
            int head = 0, tail = 1;
            while (head < tail) {
                short u = q[head++]; visit[u] = false;
                for (short i=0; i<cnt[u]; ++i) {
                    const edge& ee = e[g[u][i]];
                    if (ee.cap > ee.flow && d[ee.v] > d[u]+ee.cost) {
                        d[ee.v] = d[u]+ee.cost;
                        p[ee.v] = g[u][i];
                        a[ee.v] = min(a[u], short(ee.cap-ee.flow));
                        if (!visit[ee.v]) visit[q[tail++] = ee.v] = true;
                    }
                }
            }
            if (d[n+1] >= 1e39) break;
            ans += d[n+1];
            for (short u=n+1; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[n+1];
                e[p[u]^1].flow -= a[n+1];
            }
        }
        cout << "Case " << ++kase << ": " << (ans<0. ? -ans : 0.) << endl;
    }
    return 0;
}