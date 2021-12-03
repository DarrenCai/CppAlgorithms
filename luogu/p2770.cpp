/**
 * p2770 航空路线问题
 */

#include <iostream>
#include <cstring>
#include <string>
#include <map>
using namespace std;

#define N 220
struct edge {short u, v, cap, flow, cost;} e[N*N>>2];
short g[N][N>>1], q[N*N*N>>2], a[N], d[N], p[N], cnt[N], m, n, c; string s[N>>1]; bool visit[N];

void addEdge(short u, short v, short cap, short cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) {
        short t = 2*n-1, cc = 0, flow = 0; map<string, short> id;
        for (short i=0; i<n; ++i) cin >> s[i], id[s[i]] = i;
        if (n==1) {
            cout << 1 << endl << s[0] << endl;
            continue;
        }
        memset(cnt, c = 0, sizeof(cnt));
        addEdge(0, n, 2, 0); addEdge(t-n, t, 2, 0);
        for (short i=2; i<n; ++i) addEdge(i-1, i+n-1, 1, 0);
        for (short i=0; i<m; ++i) {
            string s1, s2; cin >> s1 >> s2;
            short x = id[s1], y = id[s2];
            if (x > y) x = x+y, y = x-y, x = x-y;
            addEdge(x+n, y, x==0 && y==n-1 ? 2 : 1, -1);
        }
        while (true) {
            memset(d, 1, sizeof(d)); memset(visit, 0, sizeof(visit));
            d[0] = 0; q[0] = 0; a[0] = 1;
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
            if (d[t] >= 0) break;
            cc -= d[t];
            flow += 1;
            for (short u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        if (flow == 2) {
            cout << cc << endl;
            cout << s[0] << endl;
            short u = n;
            while (u != t) {
                for (short i=0, j; i<cnt[u]; ++i) if (e[j = g[u][i]].flow > 0) {
                    cout << s[e[j].v] << endl;
                    u = e[j].v + n;
                    --e[j].flow; ++e[j+1].flow;
                    break;
                }
            }
            u = t-n;
            while (u != 0) {
                for (short i=0, j; i<cnt[u]; ++i) if (e[j = g[u][i]].flow < 0) {
                    cout << s[e[j].v-n] << endl;
                    u = e[j].v - n;
                    ++e[j].flow; --e[j-1].flow;
                    break;
                }
            }
        } else cout << "No Solution!" << endl;
    }
    return 0;
}