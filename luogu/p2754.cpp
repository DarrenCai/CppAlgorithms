/**
 * p2754 星际转移问题
 */

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define M 23
#define N 600000
struct edge {int u, v, cap, flow;} e[M*N<<1]; vector<int> g[N];
int p[N], a[N], h[M], r[M], s[M][M], m, n, k, c; bool g0[M][M];

void addEdge(int u, int v, int cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u].push_back(c++);
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v].push_back(c++);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m >> k) {
        memset(g0, c=0, sizeof(g0)); ++n;
        for (int i=0; i<m; ++i) {
            cin >> h[i] >> r[i];
            for (int j=0; j<r[i]; ++j) {
                cin >> s[i][j];
                if (s[i][j] < 0) s[i][j] = n;
            }
            g0[s[i][r[i]-1]][s[i][0]] = true;
            for (int j=1; j<r[i]; ++j) g0[s[i][j-1]][s[i][j]] = true;
        }
        for (int k=n; k>=0; --k) for (int i=n; i>=0; --i) for (int j=n; j>=0; --j)
            if (g0[i][k] && g0[k][j]) g0[i][j] = true;
        if (g0[0][n++]) {
            for (int i=n+1; i>=0; --i) g[i].clear();
            int flow = 0; addEdge(0, 2, k);
            for (int cc=1; cc<N; ++cc) {
                for (int i=0; i<n; ++i) g[cc*n+i+2].clear(), addEdge((cc-1)*n+i+2, cc*n+i+2, k);
                addEdge((cc+1)*n+1, 1, k);
                for (int i=0, j; i<m; ++i) {
                    (j = cc%r[i]) ? addEdge((cc-1)*n+s[i][j-1]+2, cc*n+s[i][j]+2, h[i])
                                    : addEdge((cc-1)*n+s[i][r[i]-1]+2, cc*n+s[i][0]+2, h[i]);
                }
                while (true) {
                    memset(a, 0, sizeof(a)); a[0] = k; vector<int> q; q.push_back(0);
                    int head = 0, tail = 1;
                    while (head < tail) {
                        int u = q[head++];
                        for (int i=g[u].size()-1; i>=0; --i) {
                            const edge& ee = e[g[u][i]];
                            if (!a[ee.v] && ee.cap > ee.flow) {
                                p[ee.v] = g[u][i];
                                a[ee.v] = min(a[u], ee.cap-ee.flow);
                                q.push_back(ee.v);
                                tail++;
                            }
                        }
                        if (a[1]) break;
                    }
                    if (!a[1] || (flow += a[1]) == k) break;
                    for (int u=1; u!=0; u=e[p[u]].u) {
                        e[p[u]].flow += a[1];
                        e[p[u]^1].flow -= a[1];
                    }
                }
                if (flow == k) {
                    cout << cc << endl; break;
                }
            }
        } else cout << 0 << endl;
    }
    return 0;
}