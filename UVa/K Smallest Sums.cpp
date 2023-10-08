/**
 * UVa11997
 * K个最小和
 */

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define K 752
int s[2][K], k;
struct sum {
    int s, b;
    sum(int s, int b):s(s), b(b) {}
    bool operator< (const sum& rhs) const {
        return s != rhs.s ? s > rhs.s : b > rhs.b;
    }
};

void solve() {
    for (int i=0; i<k; ++i) cin >> s[0][i];
    sort(s[0], s[0]+k);
    for (int i=1; i<k; ++i) {
        for (int j=0; j<k; ++j) cin >> s[1][j];
        sort(s[1], s[1]+k);
        priority_queue<sum> q;
        for (int j=0; j<k; ++j) q.push(sum(s[0][j]+s[1][0], 0));
        for (int j=0; j<k; ++j) {
            sum t = q.top(); q.pop(); s[0][j] = t.s;
            if (t.b+1 < k) q.push(sum(t.s-s[1][t.b]+s[1][t.b+1], t.b+1));
        }
    }
    cout << s[0][0];
    for (int i=1; i<k; ++i) cout << ' ' << s[0][i];
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin >> k) solve();
    return 0;
}