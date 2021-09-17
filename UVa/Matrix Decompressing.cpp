/**
 * UVa11082
 * 矩阵解压
 */

#include <iostream>
using namespace std;

#define N 20
struct edge {short u, v, cap, flow;} e[(N+2)*N<<1]; short g[(N+1)<<1][N+1], q[(N+2)*N<<1], p[(N+1)<<1], sr[N], sc[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    sr[0] = sc[0] = 0;
    short t; cin >> t;
    for (short x=1; x<=t; ++x) {
        short r, c, tt, cc = 0, cnt[(N+1)<<1] = {0}; cin >> r >> c; tt = r+c+1;
        for (short i=1; i<=r; ++i) cin >> sr[i];
        for (short i=r; i>0; --i) sr[i] -= sr[i-1];
        for (short i=1; i<=c; ++i) cin >> sc[i];
        for (short i=c; i>0; --i) sc[i] -= sc[i-1];
        for (short i=1; i<=r; ++i) {
            e[cc].u = 0; e[cc].v = i; e[cc].cap = sr[i]-c; e[cc].flow = 0; g[0][cnt[0]++] = cc++;
            e[cc].u = i; e[cc].v = 0; e[cc].cap = 0; e[cc].flow = 0; g[i][cnt[i]++] = cc++;
            for (short j=r+1; j<tt; ++j) {
                e[cc].u = i; e[cc].v = j; e[cc].cap = N-1; e[cc].flow = 0; g[i][cnt[i]++] = cc++;
                e[cc].u = j; e[cc].v = i; e[cc].cap = 0; e[cc].flow = 0; g[j][cnt[j]++] = cc++;
            }
        }
        for (short i=r+1; i<tt; ++i) {
            e[cc].u = i; e[cc].v = tt; e[cc].cap = sc[i-r]-r; e[cc].flow = 0; g[i][cnt[i]++] = cc++;
            e[cc].u = tt; e[cc].v = i; e[cc].cap = 0; e[cc].flow = 0; g[tt][cnt[tt]++] = cc++;
        }
        while (true) {
            short head = 0, tail = 1, a[(N+1)<<1] = {0}; a[0] = r*N; q[0] = 0;
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
                if (a[tt]) break;
            }
            if (!a[tt]) break;
            for (short u=tt; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[tt];
                e[p[u]^1].flow -= a[tt];
            }
        }
        cout << "Matrix " << x << endl;
        for (short i=1; i<=r; ++i) {
            cout << 1+e[g[i][1]].flow;
            for (short j=2; j<=c; ++j) cout << ' ' << 1+e[g[i][j]].flow;
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}