/**
 * UVa753
 * UNIX插头
 */

#include <iostream>
#include <cstring>
#include <string>
#include <map>
using namespace std;

#define N 105
map<string, short> ids;
struct edge {short u, v, cap, flow;} e[4*N*N];
int g[3*N][3*N], a[3*N], p[3*N], q[4*N*N], rece[N], device[N], adapt[N][2], cnt[3*N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        ids.clear();
        memset(cnt, 0, sizeof(cnt));
        int n, m, k, c = 0, es = 0; string s;
        cin >> n;
        for (short i=1; i<=n; ++i) {
            cin >> s;
            rece[i] = ids.count(s) ? ids[s] : ids[s] = c++;
        }
        cin >> m;
        for (short i=1; i<=m; ++i) {
            cin >> s >> s;
            device[i] = ids.count(s) ? ids[s] : ids[s] = c++;
        }
        cin >> k;
        for (short i=1; i<=k; ++i) {
            cin >> s;
            adapt[i][0] = ids.count(s) ? ids[s] : ids[s] = c++;
            cin >> s;
            adapt[i][1] = ids.count(s) ? ids[s] : ids[s] = c++;
        }
        for (short i=1; i<=m; ++i) {
            e[es].u = 0; e[es].v = i; e[es].cap = 1; e[es].flow = 0;
            g[0][cnt[0]++] = es++;
            e[es].u = i; e[es].v = 0; e[es].cap = 0; e[es].flow = 0;
            g[i][cnt[i]++] = es++;
        }
        for (short i=1; i<=m; ++i) for (short j=1; j<=k; ++j) if (device[i] == adapt[j][0]) {
            short v = m+j;
            e[es].u = i; e[es].v = v; e[es].cap = 1; e[es].flow = 0;
            g[i][cnt[i]++] = es++;
            e[es].u = v; e[es].v = i; e[es].cap = 0; e[es].flow = 0;
            g[v][cnt[v]++] = es++;
        }
        for (short i=1; i<=k; ++i) for (short j=1; j<=k; ++j) if (adapt[i][1] == adapt[j][0]) {
            short u = m+i, v = m+j;
            e[es].u = u; e[es].v = v; e[es].cap = N; e[es].flow = 0;
            g[u][cnt[u]++] = es++;
            e[es].u = v; e[es].v = u; e[es].cap = 0; e[es].flow = 0;
            g[v][cnt[v]++] = es++;
        }
        for (short i=1; i<=m; ++i) for (short j=1; j<=n; ++j) if (device[i] == rece[j]) {
            short v = m+k+j;
            e[es].u = i; e[es].v = v; e[es].cap = 1; e[es].flow = 0;
            g[i][cnt[i]++] = es++;
            e[es].u = v; e[es].v = i; e[es].cap = 0; e[es].flow = 0;
            g[v][cnt[v]++] = es++;
        }
        for (short i=1; i<=k; ++i) for (short j=1; j<=n; ++j) if (adapt[i][1] == rece[j]) {
            short u = m+i, v = m+k+j;
            e[es].u = u; e[es].v = v; e[es].cap = 1; e[es].flow = 0;
            g[u][cnt[u]++] = es++;
            e[es].u = v; e[es].v = u; e[es].cap = 0; e[es].flow = 0;
            g[v][cnt[v]++] = es++;
        }
        for (short i=1; i<=n; ++i) {
            short u = m+k+i, v = m+k+n+1;
            e[es].u = u; e[es].v = v; e[es].cap = 1; e[es].flow = 0;
            g[u][cnt[u]++] = es++;
            e[es].u = v; e[es].v = u; e[es].cap = 0; e[es].flow = 0;
            g[v][cnt[v]++] = es++;
        }
        short flow = 0;
        while (true) {
            memset(a, 0, sizeof(a)); a[0] = N;
            int head = 0, tail = 1, tt = m+k+n+1; q[0] = 0;
            while (head < tail) {
                short x = q[head++];
                for (short i=0; i<cnt[x]; ++i) {
                    const edge& ee = e[g[x][i]];
                    if (!a[ee.v] && ee.cap > ee.flow) {
                        p[ee.v] = g[x][i];
                        a[ee.v] = min(a[x], ee.cap-ee.flow);
                        q[tail++] = ee.v;
                    }
                }
                if (a[tt]) break;
            }
            if (!a[tt]) break;
            for (short u=tt; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[tt];
                e[p[u]^1].flow -= a[tt];
            }
            flow += a[tt];
        }
        cout << m - flow << endl;
        if (t) cout << endl;
    }
    return 0;
}