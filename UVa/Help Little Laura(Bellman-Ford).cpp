/**
 * UVa1659
 * 帮助小罗拉
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

bool bellman_ford() {
    fill(d, d+N, 1e39);
    memset(visit, 0, sizeof(visit));
    memset(cnt0, 0, sizeof(cnt0));
    d[0] = 0.; q[0] = 0; p[0] = 0; a[0] = M;
    int head = 0, tail = 1;
    while (head < tail) {
        short u = q[head++]; visit[u] = false;
        for (short i=0; i<cnt[u]; ++i) {
            const edge& ee = e[g[u][i]];
            if (ee.cap > ee.flow && d[ee.v] > d[u]+ee.cost) {
                d[ee.v] = d[u]+ee.cost;
                p[ee.v] = g[u][i];
                a[ee.v] = min(a[u], short(ee.cap-ee.flow));
                if (!visit[ee.v]) {
                    visit[q[tail++] = ee.v] = true;
                    if (++cnt0[ee.v] > n) {
                        short u = ee.v, v; bool circle = false;
                        memset(cnt0, 0, sizeof(cnt0));
                        do {
                            if (++cnt0[u] > 1) {
                                circle = true;
                                v = u;
                                break;
                            }
                        } while ((u=e[p[u]].u) != 0);
                        do {
                            ans += e[p[v]].cost;
                            e[p[v]].flow += 1;
                            e[p[v]^1].flow -= 1;
                        } while ((v=e[p[v]].u) != u);
                        return circle;
                    }
                }
            }
        }
    }
    return false;
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
        for (short u=1; u<=n; ++u) addEdge(0, u, 1, 0.);
        for (short u=1; u<=n; ++u) for (short i=0; i<cnt0[u]; ++i) {
            short v = g0[u][i]; double cc = t-s*sqrt(pow(x[u]-x[v],2)+pow(y[u]-y[v],2));
            addEdge(u, v, 1, cc);
        }
        ans = 0.;
        while (bellman_ford());
        cout << "Case " << ++kase << ": " << (ans<0. ? -ans : 0.) << endl;
    }
    return 0;
}