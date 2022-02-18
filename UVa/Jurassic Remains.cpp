/**
 * UVa1326
 * 侏罗纪
 */

#include <iostream>
#include <string>
using namespace std;

#define N 24
struct node {int s, n, d;} q[1<<N]; int d[N], n;

void print(int s, int k) {
    cout << k << endl;
    if (k) for (int i=0; i<n; ++i) if (s & (1<<i)) {
        cout << i+1;
        if (--k) cout << ' ';
    }
    cout << endl;
}

void bfs(int s, int d) {
    int head = 0, tail = 1, k = n-1, t = 1;
    q[0].s = s; q[0].n = n-1; q[0].d = d;
    while (head < tail) {
       const node& p = q[head++];
       for (int i=p.n; i>=0; --i) {
           s = p.s ^ (1<<i);
           d = p.d ^ ::d[i];
           if (!d) return print(s, k);
           if (i > 0) if (i > 0) q[t].s = s, q[t].n = i-1, q[t++].d = d;
       }
       if (head == tail) --k, tail = t;
    }
    print(0, 0);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) {
        int v = 0, s = (1<<n)-1;
        for (int i=0; i<n; ++i) {
            string s; cin >> s; d[i] = 0;
            for (int j=s.size()-1; j>=0; --j) d[i] ^= 1<<(s[j]-'A');
            v ^= d[i];
        }
        v ? bfs(s, v) : print(s, n);
    }
    return 0;
}