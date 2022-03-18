/**
 * UVa1316/LA2757
 * 超市
 */

#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

#define N 10050
struct prod {
    short d, p;
    bool operator< (const prod& rhs) const {
        return d > rhs.d;
    }
} s[N];
struct cmp {
    bool operator() (short i, short j) const {
        return s[i].p > s[j].p || (s[i].p==s[j].p && i<j);
    }
};

int solve(short n) {
    int ans = 0; short d = 0, cur = 0;
    for (short i=0; i<n; ++i) cin >> s[i].p >> s[i].d, d = max(d, s[i].d);
    sort(s, s+n);
    set<short, cmp> q;
    while (d > 0) {
        while (cur<n && s[cur].d>=d) q.insert(cur++);
        if (!q.empty()) {
            set<short, cmp>::iterator it = q.begin();
            ans += s[*it].p;
            q.erase(it);
        }
        --d;
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n;
    while (cin >> n) cout << solve(n) << endl;
    return 0;
}
