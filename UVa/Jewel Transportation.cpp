/**
 * UVa12344
 */

#include <iostream>
#include <iomanip>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 16;
const int MAXM = 100;
const int MAXK = 5;

struct Edge {
    int u, v;
    int cost[MAXK];
};

int n, m, k;
vector<Edge> edges;
int sr[MAXK], tr[MAXK];
int dist[MAXK][MAXN];                 // dist[i][v] = min cost from v to tr[i]
vector<vector<int>> adj;              // original graph adjacency list (edge indices)
vector<vector<pair<int,int>>> radj;   // reverse graph: (from, edge_idx)
vector<int> sortedAdj[MAXK][MAXN];    // sorted adjacency for each jewelry i and node u
bitset<MAXM> usedMask;
vector<int> order;                    // jewelry processing order
int bestCost = INF;
vector<int> bestPaths[MAXK];

// ---------- Dijkstra for shortest path from every node to tr[i] ----------
void dijkstra(int idx) {
    vector<int> d(n, INF);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    d[tr[idx]] = 0;
    pq.push({0, tr[idx]});
    while (!pq.empty()) {
        auto [du, u] = pq.top(); pq.pop();
        if (du != d[u]) continue;
        for (auto [v, e] : radj[u]) {   // reverse edge: original edge e: v -> u
            if (d[v] > du + edges[e].cost[idx]) {
                d[v] = du + edges[e].cost[idx];
                pq.push({d[v], v});
            }
        }
    }
    for (int i = 0; i < n; ++i) dist[idx][i] = d[i];
}

// ---------- Greedy for a given order ----------
bool greedyForOrder(const vector<int>& ord, int& totalCost, vector<int> paths[MAXK]) {
    bitset<MAXM> used;
    totalCost = 0;
    for (int idx : ord) {
        int i = idx;
        if (sr[i] == tr[i]) {
            paths[i].clear();
            continue;
        }
        vector<int> d(n, INF), parent(n, -1), parentEdge(n, -1);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        d[sr[i]] = 0;
        pq.push({0, sr[i]});
        while (!pq.empty()) {
            auto [du, u] = pq.top(); pq.pop();
            if (du != d[u]) continue;
            for (int e : adj[u]) {
                if (used[e]) continue;
                int v = edges[e].v;
                if (d[v] > du + edges[e].cost[i]) {
                    d[v] = du + edges[e].cost[i];
                    parent[v] = u;
                    parentEdge[v] = e;
                    pq.push({d[v], v});
                }
            }
        }
        if (d[tr[i]] == INF) return false;
        vector<int> path;
        int cur = tr[i];
        while (cur != sr[i]) {
            int e = parentEdge[cur];
            path.push_back(e);
            used.set(e);
            cur = parent[cur];
        }
        reverse(path.begin(), path.end());
        paths[i] = path;
        totalCost += d[tr[i]];
    }
    return true;
}

// ---------- Initial upper bound by trying all permutations ----------
void getInitialSolution() {
    vector<int> perm(k);
    iota(perm.begin(), perm.end(), 0);
    do {
        vector<int> tmpPaths[MAXK];
        int cost;
        if (greedyForOrder(perm, cost, tmpPaths)) {
            if (cost < bestCost) {
                bestCost = cost;
                for (int i = 0; i < k; ++i) bestPaths[i] = tmpPaths[i];
            }
        }
    } while (next_permutation(perm.begin(), perm.end()));
}

// ---------- DFS search ----------
void search(int idx, int curCost, const bitset<MAXM>& used, const vector<int> paths[MAXK]);

// Enumerate all simple paths for current jewelry i
void enumPaths(int i, int idx, int curCost, const bitset<MAXM>& used,
               const vector<int> paths[MAXK],
               bitset<MAXM> pathMask, int u, int mask,
               int pcost, const vector<int>& pedges, int remainAfter) {
    if (u == tr[i]) {
        // Complete path for this jewelry
        vector<int> newPaths[MAXK];
        for (int j = 0; j < k; ++j) newPaths[j] = paths[j];
        newPaths[i] = pedges;
        bitset<MAXM> newUsed = used | pathMask;
        search(idx + 1, curCost + pcost, newUsed, newPaths);
        return;
    }

    // Prune: current partial path + lower bound of remaining part for this jewelry + lower bound of later jewelry
    if (pcost + dist[i][u] + remainAfter >= bestCost) return;

    for (int e : sortedAdj[i][u]) {
        int v = edges[e].v;
        if (mask & (1 << v)) continue;
        if (used[e] || pathMask[e]) continue;
        if (pcost + edges[e].cost[i] + dist[i][v] + remainAfter >= bestCost) continue;
        bitset<MAXM> newPathMask = pathMask;
        newPathMask.set(e);
        vector<int> newPedges = pedges;
        newPedges.push_back(e);
        enumPaths(i, idx, curCost, used, paths,
                  newPathMask, v, mask | (1 << v),
                  pcost + edges[e].cost[i], newPedges, remainAfter);
    }
}

void search(int idx, int curCost, const bitset<MAXM>& used, const vector<int> paths[MAXK]) {
    if (idx == k) {
        if (curCost < bestCost) {
            bestCost = curCost;
            for (int i = 0; i < k; ++i) bestPaths[i] = paths[i];
        }
        return;
    }

    int i = order[idx];

    // Lower bound for remaining jewelry
    int remain = 0;
    for (int j = idx; j < k; ++j) {
        int id = order[j];
        remain += dist[id][sr[id]];
    }
    if (curCost + remain >= bestCost) return;

    if (sr[i] == tr[i]) {
        vector<int> newPaths[MAXK];
        for (int j = 0; j < k; ++j) newPaths[j] = paths[j];
        newPaths[i].clear();
        search(idx + 1, curCost, used, newPaths);
        return;
    }

    // Lower bound for jewelry after idx
    int remainAfter = 0;
    for (int j = idx + 1; j < k; ++j) {
        int id = order[j];
        remainAfter += dist[id][sr[id]];
    }

    bitset<MAXM> pathMask;
    vector<int> pedges;
    enumPaths(i, idx, curCost, used, paths,
              pathMask, sr[i], 1 << sr[i], 0, pedges, remainAfter);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    while (cin >> n >> m >> k) {
        if (n == 0 && m == 0 && k == 0) break;

        edges.resize(m);
        adj.assign(n, {});
        radj.assign(n, {});
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            edges[i].u = a;
            edges[i].v = b;
            for (int j = 0; j < k; ++j) cin >> edges[i].cost[j];
            adj[a].push_back(i);
            radj[b].push_back({a, i});
        }

        for (int i = 0; i < k; ++i) {
            cin >> sr[i] >> tr[i];
            --sr[i]; --tr[i];
        }

        // Dijkstra for each jewelry
        bool reachable = true;
        for (int i = 0; i < k; ++i) {
            dijkstra(i);
            if (dist[i][sr[i]] >= INF) reachable = false;
        }
        if (!reachable) {
            cout << -1 << "\n";
            continue;
        }

        // Pre-sort adjacency for each jewelry according to dist to target
        for (int i = 0; i < k; ++i) {
            for (int u = 0; u < n; ++u) {
                sortedAdj[i][u] = adj[u];
                sort(sortedAdj[i][u].begin(), sortedAdj[i][u].end(),
                     [&](int e1, int e2) {
                         int v1 = edges[e1].v, v2 = edges[e2].v;
                         return dist[i][v1] < dist[i][v2];
                     });
            }
        }

        // Determine processing order: by shortest distance descending
        order.resize(k);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return dist[a][sr[a]] > dist[b][sr[b]];
        });

        bestCost = INF;
        for (int i = 0; i < k; ++i) bestPaths[i].clear();

        // Try greedy initial solution
        getInitialSolution();

        // Full search
        bitset<MAXM> emptyUsed;
        vector<int> emptyPaths[MAXK];
        search(0, 0, emptyUsed, emptyPaths);

        if (bestCost == INF) {
            cout << -1 << "\n";
        } else {
            cout << bestCost << "\n";
            for (int i = 0; i < k; ++i) {
                cout << bestPaths[i].size();
                sort(bestPaths[i].begin(), bestPaths[i].end());
                for (int e : bestPaths[i]) cout << " " << e + 1;
                cout << "\n";
            }
        }
    }

    return 0;
}