/**
 * UVa1663
 * 净化器
 */

#include <iostream>
#include <cstring>
#include <string>
#include <map>
using namespace std;

#define M 2200

struct edge{short u, v, cap, flow;} e[12*M];
short g[M][M/2], q[12*M*M], p[M], a[M], cnt[M], n, m, c;

void addEdge(short u, short v, short cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m && n) {
        map<string, short> id;
        for (short i=1; i<=m; ++i) {
            string s; cin >> s; short f = -1;
            for (short j=0; j<n; ++j) if (s[j]=='*') {
                f = j; break;
            }
            if (f >= 0) {
                s[f] = '0';
                if (!id.count(s)) id[s] = id.size();
                s[f] = '1';
                if (!id.count(s)) id[s] = id.size();
            } else if (!id.count(s)) id[s] = id.size();
        }
        memset(cnt, c=0, sizeof(cnt));
        short t = 2*id.size() + 1;
        for (short i=id.size(); i>0; --i) addEdge(0, 2*i-1, 1), addEdge(2*i, t, 1);
        for (map<string, short>::iterator it = id.begin(); it != id.end(); ++it) {
            const string& a = it->first; short x = it->second;
            for (map<string, short>::iterator it1 = it; ++it1 != id.end();) {
                const string& b = it1->first; short d = 0, y = it1->second;
                for (short i=0; i<n; ++i) if (a[i]!=b[i] && ++d>1) break;
                if (d==1) addEdge(2*x+1, 2*y+2, 1), addEdge(2*y+1, 2*x+2, 1);
            }
        }
        short flow = 0;
        while (true) {
            memset(a, 0, sizeof(a)); a[0] = 1; q[0] = 0;
            int head = 0, tail = 1;
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
                if (a[t]) break;
            }
            if (!a[t]) break;
            flow += a[t];
            for (short u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        cout << id.size()-flow/2 << endl;
    }
    return 0;
}