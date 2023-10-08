/**
 * UVa11995
 * 猜猜数据结构
 */

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

#define N 1005
short a[N], x[N], n;

short judge() {
    short r = 7; stack<short> s; queue<short> q; priority_queue<short> p;
    for (int i=0; i<n; ++i) {
        if (a[i] == 1) s.push(x[i]), q.push(x[i]), p.push(x[i]);
        else {
            if (s.empty()) return 0;
            if (r&1 && s.top()!=x[i]) r ^= 1;
            if (r&2 && q.front()!=x[i]) r ^= 2;
            if (r&4 && p.top()!=x[i]) r ^= 4;
            s.pop(); p.pop(); q.pop();
        }
    }
    return r;
}

void solve() {
    for (int i=0; i<n; ++i) cin >> a[i] >> x[i];
    short r = judge();
    cout << (!r ? "impossible" : (r==1 ? "stack" : (r==2 ? "queue" : (r==4 ? "priority queue" : "not sure")))) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) solve();
    return 0;
}