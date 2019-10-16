/**
 * UVa1153
 * 顾客是上帝
 */

#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

#define N 800010
struct order {
    short q; int d;
    bool operator< (const order& r) const {
        return d < r.d || (d==r.d && q < r.q);
    }
};
order o[N]; int n, t;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int k; cin >> k;
    while (k--) {
        multiset<int> s; t = 0; cin >> n;
        for (int i=0; i<n; ++i) cin >> o[i].q >> o[i].d;
        sort(o, o+n);
        for (int i=0; i<n; ++i)
            if (t + o[i].q <= o[i].d) {
                s.insert(o[i].q);
                t += o[i].q;
            } else if (!s.empty()) {
                int m = *s.rbegin();
                if (o[i].q < m) {
                    s.erase(s.find(m));
                    s.insert(o[i].q);
                    t += o[i].q - m;
                }
            }
        cout << s.size() << endl;
        if (k) cout << endl;
    }
    return 0;
}