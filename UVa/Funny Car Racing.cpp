/**
 * UVa12661
 * 有趣的赛车比赛
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 350
#define M 50500
struct edge {short u, v; int a, b, t;} e[M];
long long d[N]; int g[N][M], cnt[N];
struct {long long d; short u;} q[N*M];

long long calc(long long t, const edge& e) {
    long long x = t/e.b*e.b, y = t+e.t;
    return y <= x+e.a ? y : x+e.b+e.t;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short kase = 0, n, s, t; int m;
    while (cin >> n >> m >> s >> t) {
        memset(cnt, 0, sizeof(cnt)); memset(d, -1, sizeof(d)); d[s] = 0;
        for (int i=0; i<m; ++i) {
            cin >> e[i].u >> e[i].v >> e[i].a >> e[i].b >> e[i].t;
            if (e[i].a < e[i].t) {
                --i; --m;
                continue;
            }
            e[i].b += e[i].a;
            g[e[i].u][cnt[e[i].u]++] = i;
        }
        q[0].d = 0; q[0].u = s;
        int head = 0, tail = 1;
        while (head < tail) {
            short u = q[head].u;
            if (q[head++].d > d[u]) continue;
            for (int i=0; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]]; short v = ee.v;
                long long w = calc(d[u], ee);
                if (d[v] < 0 || d[v] > w) {
                    d[v] = w; q[tail].d = w; q[tail++].u = v;
                }
            }
        }
        cout << "Case " << ++kase << ": " << d[t] << endl;
    }
    return 0;
}