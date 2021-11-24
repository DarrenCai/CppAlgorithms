/**
 * UVa12264
 * Risk游戏
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 330
struct edge {short u, v, cap, flow;} e[N*N/2];
short q[N*N*N/2], g0[N][N], c0[N], a[N], cnt[N], m, n, t; int g[N][N], p[N], c; char s[N]; bool b[N];

void addEdge(short u, short v, short cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

short maxFLow() {
    short flow = 0;
    while (true) {
        memset(a, 0, sizeof(a)); a[0] = N; q[0] = 0;
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
        for (short u=t; u!=0; u=e[p[u]].u) {
            e[p[u]].flow += a[t];
            e[p[u]^1].flow -= a[t];
        }
    }
    return flow;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short k; cin >> k;
    while (cin >> n) {
        memset(c0, m=0, sizeof(c0)); memset(b, 0, sizeof(b)); memset(cnt, c=0, sizeof(cnt));
        for (short i=1; i<=n; ++i) {
            cin >> a[i];
            if (a[i]-- > 0) q[p[i] = ++m] = i;
        }
        for (short i=1; i<=n; ++i) {
            cin >> s+1;
            if (a[i]>=0) for (short j=1; j<=n; ++j) if (s[j]=='Y') 
                a[j] < 0 ? b[p[i]] = true : g0[p[i]][c0[p[i]]++] = p[j];
        }
        short low = 0, high = 20000, tt = 0, sum = 0;
        for (short i=1; i<=m; ++i) {
            if (b[i]) {
                c0[i] == 0 ? high = min(high, a[q[i]]) : (++tt, sum += a[q[i]]);
            } else sum += a[q[i]];
        }
        if (tt) high = min(high, short(sum/tt));
        t = 3*m+1; tt = 0;
        for (short i=1; i<=m; ++i) {
            addEdge(i, t, 0);
            if (b[i]) ++tt;
        }
        for (short i=1; i<=m; ++i) {
            addEdge(0, i+m, a[q[i]]); addEdge(i+m, i, N); addEdge(i+2*m, i+m, 1);
            for (short j=0; j<c0[i]; ++j) {
                addEdge(i+m, g0[i][j]+2*m, 1), addEdge(i+m, g0[i][j], N);
            }
        }
        while (low <= high) {
            short mid = (low + high) >> 1;
            for (short i=1; i<=m; ++i) if(b[i]) e[g[i][0]].cap = mid;
            for (int i=0; i<c; ++i) e[i].flow = 0;
            maxFLow() == tt*mid ? low = mid+1 : high = mid-1;
        }
        cout << high+1 << endl;
    }
    return 0;
}