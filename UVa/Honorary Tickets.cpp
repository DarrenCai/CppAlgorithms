/**
 * UVa11895
 * 抽奖
 */

#include <iostream>
#include <queue>
using namespace std;

#define N 100010

int gcd(int a, int b) {
    if (a > b) return gcd(b, a);
    if (a == 0) return b;
    if (a & 1) {
        if (b & 1) return gcd(a, (b-a)>>1);
        return gcd(a, b >> 1);
    } else {
        if (b & 1) return gcd(a >> 1, b);
        return gcd(a >> 1, b >> 1) << 1;
    }
}

struct node {
    long long t, p, q; bool f;
    bool operator< (const node& rhs) const {
        __uint128_t a = p, b = rhs.p;
        return a*rhs.q*rhs.t < b*q*t;
    }
    void take() {
        if (f) {
            long long g = gcd(p, t);
            p = p/g*(t-1);
            q *= t/g;
            f = g>1;
        } else {
            p *= t-1;
            q *= t;
        }
    }
} s[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        for (int i=0; i<n; ++i) {
            cin >> s[i].t >> s[i].p;
            s[i].q = 1; s[i].f = true;
        }
        priority_queue<node> q(s, s+n);
        while (--k) {
            node node = q.top(); q.pop();
            node.take(); q.push(node);
        }
        node node = q.top();
        if (node.f) {
            long long p = node.p, q1 = node.q, t = node.t, g = gcd(p, t);
            cout << p/g << '/' << t/g*q1 << endl;
        } else cout << node.p << '/' << node.q*node.t << endl;
    }
    return 0;
}