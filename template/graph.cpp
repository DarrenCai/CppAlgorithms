/**
 * 图论相关
 */

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

    namespace augment_path {
        // 求二分图最大匹配，增广路算法，复杂度O(VE)
        int g[N][N], c[N], px[N], py[N], vis[N], nx, ny, clk;
        bool dfs(int u) {
            vis[u] = clk;
            for (int i=0, v; i<c[u]; ++i) if (py[v = g[u][i]] < 0 || (vis[py[v]]!=clk && dfs(py[v]))) {
                px[u] = v; py[v] = u;
                return true;
            }
            return false;
        }
        int max_match() {
            memset(px, -1, sizeof(px)); memset(py, -1, sizeof(py)); memset(vis, -1, sizeof(vis));
            int cc = 0;
            for (int i=1; i<=nx; ++i) if (px[i] < 0 && dfs(clk = i)) ++cc;
            return cc;
        }
    }

    namespace hk {
        // 求二分图最大匹配，Hopcroft-Karp算法，复杂度O(E V^1/2)
        #define N 50050
        int dx[N], dy[N], px[N], py[N], vis[N], q[N], nx, ny, clk, d, INF = N<<1; vector<int> g[N];
        bool search() {
            memset(dx, -1, sizeof(dx)); memset(dy, -1, sizeof(dy)); d = INF;
            int head = 0, tail = 0;
            for (int i=1; i<=nx; ++i) if (px[i] < 0) q[tail++] = i, dx[i] = 0;
            while (head < tail) {
                int u = q[head++];
                if (dx[u] > d) break;
                for (int i=g[u].size()-1, v; i>=0; --i) if (dy[v = g[u][i]] < 0) {
                    dy[v] = dx[u] + 1;
                    py[v] < 0 ? d = dy[v] : (dx[py[v]] = dy[v] + 1, q[tail++] = py[v]);
                }
            }
            return d != INF;
        }
        bool dfs(int u) {
            for (int i=g[u].size()-1, v; i>=0; --i) if (vis[v = g[u][i]] != clk && dy[v] == dx[u]+1) {
                vis[v] = clk;
                if (py[v] >= 0 && dy[v] == d) continue;
                if (py[v] < 0 || dfs(py[v])) {
                    px[u] = v; py[v] = u;
                    return true;
                }
            }
            return false;
        }
        int max_match() {
            memset(px, -1, sizeof(px)); memset(py, -1, sizeof(py)); memset(vis, -1, sizeof(vis));
            int cc = clk = 0;
            while (search()) {
                ++clk;
                for (int i=1; i<=nx; ++i) if (px[i] < 0 && dfs(i)) ++cc;
            }
            return cc;
        }
    }

    namespace km {
        /**
         * 二分图最大权匹配，匈牙利算法（KM，Kuhn–Munkres 算法），复杂度O(n^3)。
         */
        #define INF 1e30
        #define eps 1e-9
        #define N 302
        double w[N][N], slack[N], lx[N], ly[N]; int p[N], n; bool s[N], t[N];
        bool match(int i) {
            s[i] = true;
            for (int j=1; j<=n; ++j) if (!t[j]) {
                double d = lx[i] + ly[j] - w[i][j];
                if (abs(d) < eps) {
                    t[j] = true;
                    if (!p[j] || match(p[j])) {
                        p[j] = i;
                        return true;
                    }
                } else slack[j] = min(slack[j], d);
            }
            return false;
        }
        void km() {
            for (int i=1; i<=n; ++i) {
                p[i] = 0; lx[i] = 0.; ly[i] = 0.;
                for (int j=1; j<=n; ++j) lx[i] = max(lx[i], w[i][j]);
            }
            for (int i=1; i<=n; ++i) {
                for (int j=1; j<=n; ++j) slack[j] = INF;
                while (true) {
                    for (int j=1; j<=n; ++j) s[j] = t[j] = false;
                    if (match(i)) break;
                    double a = INF;
                    for (int j=1; j<=n; ++j) if (!t[j]) a = min(a, slack[j]);
                    for (int j=1; j<=n; ++j) {
                        if (s[j]) lx[j] -= a;
                        t[j] ? ly[j] += a : slack[j] -= a;
                    }
                }
            }
        }
    }

    namespace km2 {
        /**
         * 二分图最大权匹配，匈牙利算法（KM，Kuhn–Munkres 算法），复杂度O(n^3)。
         * bfs实现方式
         */
        #define INF 1e30
        #define N 302
        double w[N][N], slack[N], lx[N], ly[N]; int pre[N], p[N], vis[N], n, clk;
        void bfs(int u) {
            for (int i=1; i<=n; ++i) pre[i] = 0, slack[i] = INF;
            int y = 0, yy = 0; p[0] = u;
            do {
                double d = INF; int x = p[y]; vis[y] = clk;
                for (int i=1; i<=n; ++i) if (vis[i] != clk) {
                    if (slack[i] > lx[x]+ly[i]-w[x][i]) slack[i] = lx[x]+ly[i]-w[x][i], pre[i] = y;
                    if (slack[i] < d) d = slack[i], yy = i;
                }
                for (int i=0; i<=n; ++i) vis[i] == clk ? (lx[p[i]]-=d, ly[i] += d) : slack[i] -= d;
                y = yy;
            } while (p[y]);
            while (y) p[y] = p[pre[y]], y = pre[y];
        }
        void km() {
            lx[0] = ly[0] = 0.; vis[0] = 0;
            for (int i=1; i<=n; ++i) {
                p[i] = 0; lx[i] = -INF; ly[i] = 0.; vis[i] = 0;
                for (int j=1; j<=n; ++j) lx[i] = max(lx[i], w[i][j]);
            }
            for (int i=1; i<=n; ++i) bfs(clk = i);
        }
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

/**
 * 找欧拉道路/回路
 */
namespace euler
{
    #define M 1010
    #define N 52
    struct edge {int u, v;} e[M];
    int g[N][M], c[N], path[M<<1], cc, m, n; bool vis[M];
    /**
     * 求欧拉道路时，一定要从奇点调用，求回路从任意点调用都可以
     * 如果深搜结束时cc != 2*m，说明欧拉道路/回路不存在
     */
    void euler(int u) {
        for (int i=0, j; i<c[u]; ++i) if (!vis[j = g[u][i]]) {
            const edge &eg = e[j]; int v = eg.u + eg.v - u;
            vis[j] = true; euler(v);
            path[cc++] = v; path[cc++] = u;
        }
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
                if (d[v] > d1) d[v] = d1, q.push({d[v], v});
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

// 最小生成树（Minimum Spanning Tree）
namespace mst {
    #define M 100010
    #define N 1010
    int f[N], use[M], m, n;
    struct edge {
        int u, v, w;
        bool operator< (const edge& rhs) const {
            return w < rhs.w;
        }
    } e[M]; 

    int find(int x) {
        return x==f[x] ? x : f[x] = find(f[x]);
    }

    int kruskal() {
        sort(e, e+m); memset(use, 0, sizeof(use));
        for (int i=0; i<n; ++i) f[i] = i;
        int cc = 0;
        for (int i=0, c=0; i<m; ++i) {
            int u = find(e[i].u), v = find(e[i].v);
            if (u == v) continue;
            f[u] = v; cc += e[i].w; use[i] = 1;
            if (++c == n-1) break;
        }
        return cc;
    }
}

/**
 * 最小有向生成树（Directed Minimum Spanning Tree）或最小树形图
 * 有向生成树（directed spanning tree）也叫树形图（arborescence）
 */
namespace dmst {
    #define M 10200
    #define N 102
    int g[N][M], c[N],      // 根据有向边信息建立邻接表
        f[N],               // 记录每个结点的前向结点
        w[N],               // 记录每个结点的前向边权
        id[N],              // 记录每个结点(缩圈后)的新编号
        vis[N],             // 访问标识：每个结点所在圈（或链）最后一个结点的编号，辅助于找环并在对缩点后的所有结点重新编号的流程
        m, n, ans;          // 边数，点数以及（存在最小树形图时的）答案
    struct edge {int u, v, w;} e0[M], e[M];

    /**
     * 朱-刘算法，时间复杂度O(VE)
     * 如果对同一组数据要多次求dmst，则需要备份原始边数据
     * Tarjan提出了一种能够在O(E+VlogV)时间内解决最小树形图问题的算法，参见https://oi-wiki.org/graph/dmst/
     */
    bool dmst(int root) {
        // memcpy(e, e0, sizeof(e));
        ans = 0;    // todo 初始化最小树形图的权值答案
        int k = n;  // 复制点数，不修改全局的点数
        while (true) {
            for (int i=0; i<k; ++i) f[i] = i;
            for (int i=0; i<m; ++i) if (e[i].u != e[i].v) { // 排除自环
                int u = e[i].u, v = e[i].v;
                if (f[v] == v || e[i].w < w[v]) f[v] = u, w[v] = e[i].w; // 选择边权最小的前向边
            }
            w[root] = 0;    // todo 根结点无前向边，故其前向边权为0
            int t = 0;      // 连通分量数
            for (int i=0; i<k; ++i) {
                if (i != root && f[i] == i) return false; // 有孤点（可能是缩圈后形成的），所以根结点为root的最小树形图不存在
                id[i] = vis[i] = -1;
            }
            for (int i=0, v; i<k; ++i) {
                ans += w[i];
                for (v = i; vis[v] != i && id[v] < 0; v = f[v]) vis[v] = i;
                if (id[v] < 0 && v != root) {
                    for (int u = f[v]; u != v; u = f[u]) id[u] = t;
                    id[v] = t++;    // 找到了一个环，直接分配新编号
                }
            }
            if (t == 0) return true; // 无圈，已经找到了根结点为root的最小树形图
            for (int i=0; i<k; ++i) if (id[i] < 0) id[i] = t++; // 对剩下的点也分配新编号
            for (int i=0; i<m; ++i) {
                int u = e[i].u, v = e[i].v;
                e[i].u = id[u]; e[i].v = id[v]; e[i].w -= w[v]; // 修改边权
            }
            k = t; root = id[root]; // 更新点数和根结点编号
        }
        return true;
    }
}