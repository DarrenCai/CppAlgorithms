/**
 * UVa1653
 * 倍数问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 10010
short a[10], t, n, head, tail;
struct node {short r, p, c;} q[N]; bool visit[N];

void solve() {
    memset(visit, 0, sizeof(visit));
    if (t == 0 || (t==1 && a[0] == 0)) return;
    head = tail = 0;
    for (short i=a[0] ? 0 : 1; i<t; ++i) {
        short r = a[i]%n;
        if (!visit[r]) {
            q[tail].r = r; q[tail].p = -1; q[tail++].c = a[i];
            visit[r] = true;
        }
        if (r == 0) return;
    }
    while (head++ < tail) for (short i=0; i<t; ++i) {
        const node &p1 = q[head-1];
        short r = (10l*p1.r+a[i])%n;
        if (!visit[r]) {
            node &p2 = q[tail++];
            p2.r = r; p2.p = head-1; p2.c = a[i];
            visit[r] = true;
        }
        if (r == 0) return;
    }
}

void print(const node& node) {
    if (node.p >= 0) print(q[node.p]);
    if (node.c >= 0) cout << node.c;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short m, kase = 0;
    while (cin >> n >> m) {
        bool f[10] = {false};
        while (m--) {
            short i; cin >> i; f[i] = true;
        }
        t = 0;
        for (short i=0; i<10; ++i) if (!f[i]) a[t++] = i;
        solve();
        if (!visit[0]) {
            cout << "Case " << ++kase << ": -1" << endl;
        } else {
            cout << "Case " << ++kase << ": ";
            print(q[tail-1]);
            cout << endl;
        }
    }
    return 0;
}