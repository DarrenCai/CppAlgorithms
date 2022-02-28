/**
 * UVa1422
 * 处理器
 */

#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

#define N 10050
short r[N], d[N], w[N], a[N], x[N], n;

bool cmp0(short i, short j) {
    return r[i] < r[j];
}

struct cmp {
    bool operator() (short i, short j) const {
        return d[i] < d[j] || (d[i]==d[j] && i<j);
    }
};

bool check(int s) {
    set<short, cmp> q; short cur = 0, c = 0, t = r[a[0]];
    while (true) {
        while (cur<n && r[a[cur]] == t) {
            x[cur] = w[cur];
            q.insert(a[cur++]);
        }
        int v = s; set<short, cmp>::iterator it = q.begin();
        while (it != q.end()) {
            short &ref = x[*it];
            if (ref <= v) {
                v -= ref; it = q.erase(it);
                if (++c == n) return true;
            } else {
                ref -= v;
                break;
            }
        }
        ++t;
        if (q.size()>0 && d[*q.begin()]==t) return false;
    }
    return false;
}

short solve() {
    int l = 0, h = 0;
    for (short i=0; i<n; ++i) {
        cin >> r[i] >> d[i] >> w[i];
        l = max(l, (w[i]+d[i]-r[i]-1)/(d[i]-r[i]));
        h += w[i];
        a[i] = i;
    }
    sort(a, a+n, cmp0);
    while (l <= h) {
        int mid = (l+h)>>1;
        check(mid) ? h = mid-1 : l = mid+1;
    }
    return l;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    short t; cin >> t;
    while (cin >> n) cout << solve() << endl;
    return 0;
}