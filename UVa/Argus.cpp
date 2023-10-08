/**
 * UVa1203/LA3135
 * 阿格斯
 * Beijing 2004
 */

#include <iostream>
#include <queue>
using namespace std;

#define N 3002
int t[N], u[N], q, k, n = 0; char buf[10];

struct cmp {
    bool operator() (int i, int j) {
        return t[i] != t[j] ? t[i] > t[j] : i > j;
    }
};

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    priority_queue<int, vector<int>, cmp> p;
    while (cin>>buf && buf[0]=='R') cin >> q >> t[q], u[q] = t[q], p.push(q);
    cin >> k;
    while (k--) q = p.top(), p.pop(), t[q] += u[q], p.push(q), cout << q << endl;
    return 0;
}