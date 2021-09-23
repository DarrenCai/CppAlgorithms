/**
 * UVa1515
 * 水塘
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 61
#define INF 100000000
struct edge {short u, v; int cap, flow;} e[8*N*N];
char s[N][N]; short g[N*N][N*N], q[8*N*N*N*N], p[N*N], cnt[N*N], c; int a[N*N];

void addEdge(short u, short v, int cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short tt; cin >> tt;
    while (tt--) {
        short w, h, d, f, b;
        memset(cnt, 0, sizeof(cnt));
        cin >> w >> h >> d >> f >> b;
        int flow = c = 0; short t = w*h+1;
        for (short x=1; x<=h; ++x) {
            cin >> s[x]+1;
            for (short y=1; y<=w; ++y) {
                short u = (x-1)*w + y;
                if (x==1 || x==h || y==1 || y==w) {
                    flow += s[x][y]=='.' ? f : 0;
                    addEdge(0, u, INF);
                } else if (s[x][y] == '#') {
                    addEdge(0, u, d);
                } else {
                    addEdge(u, t, f);
                }
                if (x>1) addEdge(u, (x-2)*w + y, b);
                if (x<h) addEdge(u, x*w + y, b);
                if (y>1) addEdge(u, (x-1)*w + y-1, b);
                if (y<w) addEdge(u, (x-1)*w + y+1, b);
            }
        }
        while (true) {
            memset(a, 0, sizeof(a)); a[0] = INF; q[0] = 0;
            int head = 0, tail = 1;
            while (head < tail) {
                short u = q[head++];
                for (short i=0; i<cnt[u]; ++i) {
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
            for (short u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        cout << flow << endl;
    }
    return 0;
}