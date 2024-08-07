/**
 * 网络流相关
 */

namespace ek
{
    /**
     * 求最大流的Edmonds–Karp算法，复杂度O(VE^2)。
     */
    #define INF 1000000000
    #define M 10000
    #define N 1000
    struct edge {int u, v, cap, flow;} e[M];
    int g[N][N], q[M*N], a[N], p[N], cnt[N], c, n; // todo 调整g[N][N]、q[M*N]的大小

    void add_edge(int u, int v, int cap) {
        e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
        e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
    }

    int max_flow() {
        // memset(cnt, c = 0, sizeof(cnt));
        // 建图 add_edge(...)
        int flow = 0, s, t; // todo 源点s，汇点t
        while (true) {
            memset(a, 0, sizeof(a)); a[s] = INF; q[0] = s;
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
                if (a[t]) break;
            }
            if (!a[t]) break;
            flow += a[t];
            for (int u=t; u!=s; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        return flow;
    }
}

namespace dinic
{
    /**
     * 求最大流的Dinic算法，复杂度O(V^2 E)。
     * 单位容量的的网络中，Dinic算法的总时间复杂度是O(E min(E^1/2, V^2/3))，
     * 更进一步，如果除源点汇点外，每个结点的出度或入度为1，则Dinic算法的总时间复杂度是O(E V^1/2)
     */
    #define M 10000
    #define N 1000
    struct edge {int u, v, cap, flow;} e[M];
    int g[N][N], q[N], d[N], cur[N], cnt[N], c, n; bool vis[N]; // todo 调整g[N][N]的大小

    void add_edge(int u, int v, int cap) {
        e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
        e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
    }

    bool bfs(int s, int t) {
        memset(vis, 0, sizeof(vis)); q[0] = s; d[s] = 1; vis[s] = true;
        int head = 0, tail = 1;
        while (head < tail) {
            int u = q[head++];
            for (int i=0; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]];
                if (!vis[ee.v] && ee.cap > ee.flow) vis[ee.v] = true, d[ee.v] = d[u] + 1, q[tail++] = ee.v;
            }
        }
        return vis[t];
    }

    int dfs(int u, int a, int t) {
        if (u==t || a==0) return a;
        int flow = 0, f;
        for (int& i = cur[u]; i<cnt[u]; ++i) {
            edge& ee = e[g[u][i]];
            if (d[u]+1 == d[ee.v] && (f = dfs(ee.v, min(a, ee.cap-ee.flow))) > 0) {
                ee.flow += f; e[g[u][i]^1].flow -= f; flow += f; a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }

    int max_flow() {
        // memset(cnt, c = 0, sizeof(cnt));
        // 建图 add_edge(...)
        int flow = 0, s, t; // todo 源点s、汇点t
        while (bfs(s, t)) {
            memset(cur, 0, sizeof(cur));
            flow += dfs(s, N, t); // todo dfs(s, k, t)
        }
        return flow;
    }
}

namespace ISAP
{
    /**
     * 求最大流的ISAP算法，比Dinic算法更高效
     */
    #define INF 1000000000
    #define M 10000
    #define N 1000
    struct edge {int u, v, cap, flow;} e[M];
    int g[N][N], q[N], p[N], d[N], cur[N], num[N], cnt[N], c, n; bool vis[N]; // todo 调整g[N][N]的大小，注意n是总结点数

    void add_edge(int u, int v, int cap) {
        e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
        e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
    }

    bool bfs(int s, int t) {
        memset(vis, 0, sizeof(vis)); memset(d, 0, sizeof(d)); q[0] = t; d[t] = 0; vis[t] = true;
        int head = 0, tail = 1;
        while (head < tail) {
            int v = q[head++];
            for (int i=0; i<cnt[v]; ++i) {
                const edge& ee = e[g[v][i]^1];
                if (!vis[ee.u] && ee.cap > ee.flow) vis[ee.u] = true, d[ee.u] = d[v] + 1, q[tail++] = ee.u;
            }
        }
        return vis[s];
    }

    int max_flow() {
        // memset(cnt, c = 0, sizeof(cnt));
        // 建图 add_edge(...)
        int flow = 0, s, t; // todo 源点s、汇点t
        if (!bfs(s, t)) return 0;
        memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
        for (int i=0; i<n; ++i) ++num[d[i]]; // todo 这里编号是从0开始的，如果数据编号是从1开始的，则需要调整，注意n是总结点数
        int u = s;
        while (d[s] < n) {   // todo 注意n是总结点数
            if (u == t) {
                int a = INF;
                for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
                for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
                flow += a; u = s;
            }
            int ok = 0;
            for (int i=cur[u]; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow && d[u] == d[ee.v] + 1) {
                    ok = 1; p[ee.v] = g[u][i]; cur[u] = i; u = ee.v;
                    break;
                }
            }
            if (!ok) {
                int m = n - 1; // todo 注意n是总结点数
                for (int i=0; i<cnt[u]; ++i) {
                    const edge& ee = e[g[u][i]];
                    if (ee.cap > ee.flow) m = min(m, d[ee.v]);
                }
                if (--num[d[u]] == 0) break;
                ++num[d[u] = m + 1]; cur[u] = 0;
                if (u != s) u = e[p[u]].u;
            }
        }
        return flow;
    }
}

namespace mcmf {
    /**
     * 最小费用最大流BellmanFord算法，BellmanFord算法还可求非最大流下的最小费用，比如：
     * 求限定流量k下的最小费用，在flow+a≥k的时候只增广k-flow单位的流量，然后终止程序；
     * 流量不固定的最小费用，在最短增广路费用非负时停止增广即可。
     */
    #define INF 200000000
    #define M 105
    #define T 2000
    struct edge {int u, v, cap, flow, cost;} e[M*T];    // todo 弧结构按需调整（cost为double等）
    int g[T][M], q[M*T*T], a[T], d[T], p[T], cnt[T], c; bool vis[T];   // todo 队列q的规模按需调整
    
    void add_edge(int u, int v, int cap, int cc) {
        e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
        e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
    }

    bool bellman_ford(int s, int t, int &flow, int& cost) {
        memset(d, 0x7f, sizeof(d)); memset(vis, 0, sizeof(vis));    // todo
        d[s] = 0; q[0] = s; a[s] = INF;
        int head = 0, tail = 1;
        while (head < tail) {
            int u = q[head++]; vis[u] = false;
            for (int i=0; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow && d[ee.v] > d[u]+ee.cost) {
                    d[ee.v] = d[u]+ee.cost;
                    p[ee.v] = g[u][i];
                    a[ee.v] = min(a[u], ee.cap-ee.flow);
                    if (!vis[ee.v]) vis[q[tail++] = ee.v] = true;
                }
            }
        }
        if (d[t] >= INF) return false;  // todo 流量不固定的最小费用，在d[t] >= 0时停止增广即可。
        flow += a[t];   // todo 求限定流量k下的最小费用，在flow+a[t]≥k的时候只增广k-flow单位的流量，然后终止程序。
        cost += d[t] * a[t];
        for (int u=t; u!=s; u=e[p[u]].u) {
            e[p[u]].flow += a[t];
            e[p[u]^1].flow -= a[t];
        }
        return true;
    }

    int mcmf(int s, int t) {
        // memset(cnt, c = 0, sizeof(cnt));
        // 建图 add_edge(...)
        int flow = 0, cost = 0;
        while (bellman_ford(s, t, flow, cost));
        return cost;
    }
}