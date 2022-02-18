/**
 * UVa1326
 * 侏罗纪
 */

#include <iostream>
#include <string>
#include <map>
using namespace std;

#define N 13
struct node {int s, n, d;} q[1<<N]; map<int, node> mp; int d[N<<1], n, m;

void print(int k, int s) {
    cout << k << endl;
    if (k) for (int i=0; i<n; ++i) if (s & (1<<i)) {
        cout << i+1;
        if (--k) cout << ' ';
    }
    cout << endl;
}

void bfs(int s, int d, int d1) {
    int head = 0, tail = 1, k = m-1, t = 1, sn = 0, ss = 0;
    q[0].s = s; q[0].n = k; q[0].d = d;
    node nd; nd.s = s; nd.n = m; mp[d] = nd;
    while (head < tail) {
       const node& p = q[head++];
       for (int i=p.n; i>=0; --i) {
           s = p.s ^ (1<<i);
           d = p.d ^ ::d[i];
           if (!d && k>sn) sn = k, ss = s;
           if (!mp.count(d)) nd.s = s, nd.n = k, mp[d] = nd;
           if (i > 0) q[t].s = s, q[t].n = i-1, q[t++].d = d;
       }
       if (head == tail) --k, tail = t;
    }
    if (n > m) {
        head = 0; tail = 1; k = n-m; t = 1; q[0].s = s = (1<<k) - 1; q[0].n = --k; q[0].d = d1;
        if (mp.count(d1)) {
            nd = mp[d1]; d1 = nd.n + n-m;
            if (d1 > sn) sn = d1, ss = nd.s | s<<m;
        }
        while (head < tail) {
            const node& p = q[head++];
            for (int i=p.n; i>=0; --i) {
                s = p.s ^ (1<<i);
                d = p.d ^ ::d[m+i];
                if (mp.count(d)) {
                    nd = mp[d]; d1 = nd.n + k;
                    if (d1 > sn) sn = d1, ss = nd.s | s<<m;
                }
                if (i > 0) q[t].s = s, q[t].n = i-1, q[t++].d = d;
            }
            if (head == tail) --k, tail = t;
        }
    }
    print(sn, ss);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) {
        int v = 0, v1 = 0; m = (n+1) >> 1; mp.clear();
        for (int i=0; i<n; ++i) {
            string s; cin >> s; d[i] = 0;
            for (int j=s.size()-1; j>=0; --j) d[i] ^= 1<<(s[j]-'A');
            v ^= d[i];
            if (i == m-1) v1 = v;
        }
        v ? bfs((1<<m)-1, v1, v^v1) : print(n, (1<<n)-1);
    }
    return 0;
}