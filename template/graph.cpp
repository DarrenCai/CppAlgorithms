/**
 * 图论相关
 **/

// 二分图判定
// 二分图的重要性质：1、二染色；2、二分图不存在长度为奇数的环（因为每一条边都是从一个集合走到另一个集合，只有走偶数次才可能回到同一个集合的同个点。）
namespace bipartite
{
    #define N 1010
    int color[N], g[N][N], c[N];
    // 判断结点u所在的连通分量是否为二分图
    // 调用前color数组初要始化为0并且赋值color[u]=1
    bool bipartite(int u) {
        for (int i=0, v; i<c[u]; ++i) {
            if (color[v = g[u][i]] == color[u]) return false;
            if (!color[v]) {
                color[v] = 3-color[u];
                if (!bipartite(v)) return false;
            }
        }
        return true;
    }
}

// 割点（cut vertex）和桥（bridge）
namespace cut_vertex_bridge
{
    #define N 1010
    int pre[N], g[N][N], c[N], clk; bool is_cut[N];
    // 调用前初始化memset(pre, clk = 0, sizeof(pre)); memset(is_cut, 0, sizeof(is_cut));
    // for (int u=0; u<n; ++u) if (!pre[u]) dfs(u);
    int dfs(int u, int fa = -1) {
        int low = pre[u] = ++clk, child = 0;
        for (int i=0, v; i<c[u]; ++i) if (!pre[v = g[u][i]]) {
            int lowv = dfs(v, u); low = min(low, lowv); ++child;
            if (lowv >= pre[u]) {
                is_cut[u] = 1;
                if (lowv > pre[u]) {
                    // 边(u, v)是桥
                }
            }
        } else if (pre[v] < pre[u] && v != fa) low = min(low, pre[v]);
        if (fa < 0 && child == 1) is_cut[u] = 0;
        return low;
    }
}

// 无向图（点）双连通分量（Biconnected Component）
namespace bcc
{
    #define N 1010
    int s[N*N][2], bcc[N][N], g[N][N], c[N], t[N], pre[N], bn[N], clk, cc, n, p;
    // 调用前初始化memset(pre, clk = 0, sizeof(pre)); memset(bn, cc = p = 0, sizeof(bn));
    // 注意双某个双连通分量bcc[i]可能只有两个顶点，不是环。
    // for (int u=0; u<n; ++u) if (!pre[u]) dfs(u);
    int dfs(int u, int fa = -1) {
        int low = pre[u] = ++clk;
        for (int i=0, v; i<c[u]; ++i) if (!pre[v = g[u][i]]) {
            s[p][0] = u; s[p++][1] = v;
            int lowv = dfs(v, u); low = min(low, lowv);
            if (lowv >= pre[u]) {
                t[++cc] = 0;
                while (true) {
                    int x = s[--p][0], y = s[p][1];
                    if (bn[x] != cc) bcc[cc][t[cc]++] = x, bn[x] = cc;
                    if (bn[y] != cc) bcc[cc][t[cc]++] = y, bn[y] = cc;
                    if (x == u && y == v) break;
                }
            }
        } else if (pre[v] < pre[u] && v != fa) {
            s[p][0] = u; s[p++][1] = v; low = min(low, pre[v]);
        }
        return low;
    }
}

// 无向图的边双连通分量（edge-biconnected component）
namespace edge_bcc
{
/**
 * 边-双连通分量可以用更简单的方法求出，分两个步骤，先做一次dfs标记出所有的桥，
 * 然后再做一次dfs找出边-双连通分量。因为边-双连通分量是没有公共结点的，所以只要在
 * 第二次dfs的时候保证不经过桥即可。
 */
}

// 有向图强连通分量（Strongly Connected Component）
namespace scc
{
    #define N 1010
    int g[N][N], c[N], s[N], sn[N], pre[N], clk, cc, n, p = 0;
    // 调用前初始化memset(pre, clk = 0, sizeof(pre)); memset(sn, cc = p = 0, sizeof(sn));
    // for (int u=0; u<n; ++u) if (!pre[u]) dfs(u);
    int dfs(int u) {
        int low = pre[u] = ++clk; s[p++] = u;
        for (int i=0, v; i<c[u]; ++i) if (!pre[v = g[u][i]]) {
            low = min(low, dfs(v));
        } else if (!sn[v]) low = min(low, pre[v]);
        if (low == pre[u]) {
            ++cc;
            while (true) {
                sn[s[--p]] = cc;
                if (s[p] == u) break;
            }
        }
        return low;
    }
}

// 2-SAT问题
namespace two_sat
{
/**
 * 利用子句建边跑SCC，判断是否有同集合的两个元素在同一个SCC中，若有则无解，否则可以得到有解方案：
 * 结点2*i所在SCC编号在2*i+1之前时，取i为真
 */
    #define N 1010
    int g[N][N], c[N], s[N], sn[N], low[N], pre[N], clk, cc, m, n, p;
    bool dfs(int u) {
        low[u] = pre[u] = ++clk; s[p++] = u;
        for (int i=0, v; i<c[u]; ++i) if (!pre[v = g[u][i]]) {
            if (!dfs(v)) return false;
            low[u] = min(low[u], low[v]);
        } else if (!sn[v]) low[u] = min(low[u], pre[v]);
        if (low[u] == pre[u]) {
            ++cc;
            while (true) {
                if (cc == sn[s[--p]^1]) return false;
                sn[s[p]] = cc;
                if (s[p] == u) break;
            }
        }
        return true;
    }
    
    // 利用子句建边：选了u就必须选v^1，这个函数随题意变化
    void add_clause(int u, int v) {
        g[u][c[u]++] = v^1; g[v][c[v]++] = u^1;
    }

    bool two_sat() {
        memset(c, p = 0, sizeof(c)); memset(pre, clk = 0, sizeof(pre)); memset(sn, cc = 0, sizeof(sn));
        // todo 利用子句建边
        m = 2*n;
        for (int u=0; u<m; ++u) if (!pre[u] && !dfs(u)) return false;
        return true;
    }
}

// Dijkstra求单源最短路（Single-Source Shortest Paths, SSSP）
namespace dijkstra {
    #include <cstring>
    #include <queue>
    using namespace std;

    #define N 1010
    struct {int v, w;} g[N][N]; int c[N], d[N], f[N];
    struct node {
        int d, u;
        bool operator< (const node& rhs) const {
            return d>rhs.d;
        }
    };

    void dijkstra(int s) {
        memset(d, 0x3f, sizeof(d)); memset(f, 0, sizeof(f));
        d[s] = 0; priority_queue<node> q; q.push({d[s], s});
        while (!q.empty()) {
            int u = q.top().u; q.pop();
            if (f[u]) continue;
            f[u] = 1;
            for (int i=0; i<c[u]; ++i) {
                int v = g[u][i].v, d1 = d[u] + g[u][i].w;
                if (d[v] > d1) d[v] = 1, q.push({d[v], v});
            }
        }
    }
}

// Bellman-Ford算法找负圈
namespace bellman_ford {
    #define N 1010
    struct {int v, w;} g[N][N]; int c[N], d[N], f[N], cnt[N], q[N*N], n;

    bool cycle() {
        int head = 0, tail = n;
        for (int i=0; i<n; ++i) cnt[i] = d[i] = 0, f[i] = 1, q[i] = i;
        while (head < tail) {
            int u = q[head++]; f[u] = 0;
            for (int i=0; i<c[u]; ++i) {
                int v = g[u][i].v, d1 = d[u] + g[u][i].w;
                if (d[v] > d1) {
                    d[v] = d1;
                    if (++cnt[v] >= n) return true;
                    if (!f[v]) q[tail++] = v, f[v] = 1;
                }
            }
        }
        return false;
    }
}