/**
 * HJ28 素数伴侣
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 105
#define M 60030
#define X 246
bool f[M] = {0}; struct edge {int u, v, cap, flow;} e[N*N<<1];
int s[N], p[N<<1], q[N<<1], a[N<<1], d[N<<1], g[N<<1][N], cnt[N<<1] = {0}, n, c;

void addEdge(int u, int v, int cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    for (int i=2; i<X; ++i) if (!f[i]) for (int j=i*i; j<M; j+=i) f[j] = true;
    cin >> n;
    for (int i=0; i<n; ++i) cin >> s[i];
    sort(s, s+n);
    int flow = 0, ss = n<<1, tt = ss+1;
    for (int i=c=0; i<n; ++i) {
        addEdge(ss, i, 1);
        addEdge(i+n, tt, 1);
        for (int j=i+1; j<n; ++j) if (!f[s[i]+s[j]]) addEdge(i, j+n, 1), addEdge(j, i+n, 1);;
    }
    while (true) {
        memset(a, 0, sizeof(a)); a[ss] = 1; q[0] = ss;
        int head = 0, tail = 1;
        while (head < tail) {
            int u = q[head++];
            for (int i=0; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]];
                if (!a[ee.v] && ee.cap > ee.flow) {
                    p[ee.v] = g[u][i];
                    a[ee.v] = min(a[u], ee.cap-ee.flow);
                    q[tail++] = ee.v;
                }
            }
            if (a[tt]) break;
        }
        if (!a[tt]) break;
        flow += a[tt];
        for (int u=tt; u!=ss; u=e[p[u]].u) {
            e[p[u]].flow += a[tt];
            e[p[u]^1].flow -= a[tt];
        }
    }
    cout << flow/2 << endl;
    return 0;
}