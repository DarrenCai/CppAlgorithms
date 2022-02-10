/**
 * UVa12124
 * 组装电脑
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

#define N 1020
struct node {
    int p, q;
    bool operator< (const node& rhs) const {
        return q < rhs.q || (q==rhs.q && p<rhs.p);
    }
    bool operator== (const node& rhs) const {
        return p==rhs.p && q==rhs.q;
    }
    bool operator< (int v) const {
        return q < v;
    }
} comp[N][N];
short c[N], n, m; int q[N], b;

int get(const node (&comp)[N], int n, int q) {
    short i = lower_bound(comp, comp+n, q) - comp; int x = comp[i].p;
    while (++i<n) if (comp[i].p < x) x = comp[i].p;
    return x;
}

int solve() {
    short low = 0, high = n-1;
    while (low <= high) {
        short mid = (low + high) >> 1; int s = 0;
        for (short i=0; i<m; ++i) s += get(comp[i], c[i], q[mid]);
        s>b ? high = mid-1 : low = mid+1;
    }
    return q[high];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        cin >> n >> b;
        map<string, short> id; string s; m = 0;
        for (short i=0; i<n; ++i) {
            c[i] = 0; cin >> s;
            short j = id.count(s) ? id[s] : id[s] = m++;
            node& cc = comp[j][c[j]++];
            cin >> s >> cc.p >> cc.q;
            q[i] = cc.q;
        }
        int mq = 0x7fffffff;
        for (short i=0; i<m; ++i) {
            sort(comp[i], comp[i]+c[i]);
            for (short j=1; j<c[i]; ++j) if (comp[i][j].q==comp[i][j-1].q) comp[i][j].p = comp[i][j-1].p;
            c[i] = unique(comp[i], comp[i]+c[i]) - comp[i];
            mq = min(mq, comp[i][c[i]-1].q);
        }
        sort(q, q+n); n = unique(q, q+n) - q;
        n = lower_bound(q, q+n, mq) - q + 1;
        cout << solve() << endl;
    }
    return 0;
}