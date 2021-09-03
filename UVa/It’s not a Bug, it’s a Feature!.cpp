/**
 * UVa658
 * 这不是bug,而是特性
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define N 20
#define M 102
struct {char s1[N+1], s2[N+1]; int w;} e[M];
struct {short i; int v;} s[1<<N][N];
long long d[1<<N]; short cnt[1<<N], n, m;
struct node {
    long long d; int u;
    node(long long d, int u):d(d),u(u) {}
    bool operator< (const node& rhs) const {
        return d > rhs.d;
    }
};


void initS(int u) {
    cnt[u] = 0;
    for (short i=0; i<m; ++i) {
        bool ok = true; int v = 0;
        for (short j=0; j<n; ++j) {
            if ((e[i].s1[j]=='-' && u&(1<<j)) || (e[i].s1[j]=='+' && ~u&(1<<j))) {
                ok = false;
                break;
            }
            if (e[i].s2[j]=='+' || (e[i].s2[j]=='0' && u&(1<<j))) v |= 1<<j;
        }
        if (ok && v!=u) s[u][cnt[u]].i = i, s[u][cnt[u]++].v = v;
    }
}

long long dijkstra() {
    memset(cnt, -1, sizeof(cnt));
    memset(d, -1, sizeof(d)); d[(1<<n)-1] = 0;
    priority_queue<node> q; q.push(node(0, (1<<n)-1));
    while (!q.empty()) {
        node p = q.top(); q.pop();
        int u = p.u;
        if (p.d > d[u]) continue;
        if (cnt[u] == -1) initS(u);
        for (short i=0; i<cnt[u]; ++i) {
            long long w = d[u] + e[s[u][i].i].w; int v = s[u][i].v;
            if (d[v] < 0 || d[v] > w) {
                d[v] = w;
                q.push(node(w, v));
            }
        }
    }
    return d[0];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short kase = 0;
    while (cin>>n>>m && n) {
        for (short i=0; i<m; ++i) cin >> e[i].w >> e[i].s1 >> e[i].s2;
        long long ans = dijkstra();
        cout << "Product " << ++kase << endl;
        if (ans < 0) {
            cout << "Bugs cannot be fixed." << endl;
        } else {
            cout << "Fastest sequence takes " << ans << " seconds." << endl;
        }
        cout << endl;
    }
    return 0;
}