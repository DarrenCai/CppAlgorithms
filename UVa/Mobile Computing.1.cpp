/**
 * UVa1354/LA3403
 * 天平难题
 */

#include <iostream>
#include <iomanip>
#include <set>
using namespace std;

#define N 130
struct mobile {
    double a, b;
    mobile(double l, double r): a(min(l, r)), b(max(l, r)) {}
    bool operator< (const mobile& rhs) const {
        return a < rhs.a || (a==rhs.a && b<rhs.b);
    }
};
short n; double w[N] = {0}, m; set<mobile> ba[N];

double solve() {
    cin >> m >> n;
    for (short i=(1<<n)-1; i>0; --i) ba[i].clear();
    for (short i=0; i<n; ++i) cin >> w[1<<i], ba[1<<i].insert(mobile(0, 0));
    if (n == 1) return 0;
    n = (1<<n)-1;
    double ans = -1;
    for (short i=1; i<=n; ++i) {
        w[i] = w[i&(i-1)] + w[i&-i];
        set<mobile> &s = ba[i];
        for (short j=(i-1)&i; (j<<1) >= i; j=(j-1)&i) {
            const set<mobile> &s1 = ba[j], &s2 = ba[i^j];
            for (set<mobile>::iterator it1 = s1.begin(); it1 != s1.end(); ++it1)
                for (set<mobile>::iterator it2 = s2.begin(); it2 != s2.end(); ++it2) {
                    double r = w[j] / w[i], l = 1 - r;
                    mobile m1(max(l + it1->a, it2->a - r), max(r + it2->b, it1->b - l));
                    mobile m2(max(l + it1->b, it2->a - r), max(r + it2->b, it1->a - l));
                    mobile m3(max(l + it1->a, it2->b - r), max(r + it2->a, it1->b - l));
                    mobile m4(max(l + it1->b, it2->b - r), max(r + it2->a, it1->a - l));
                    if (m1.a + m1.b < m) {
                        if (i < n) s.insert(m1);
                        else ans = max(m1.a + m1.b, ans);
                    }
                    if (m2.a + m2.b < m) {
                        if (i <n) s.insert(m2);
                        else ans = max(m2.a + m2.b, ans);
                    }
                    if (m3.a + m3.b < m) {
                        if (i < n) s.insert(m3);
                        else ans = max(m3.a + m3.b, ans);
                    }
                    if (m4.a + m4.b < m) {
                        if (i < n) s.insert(m4);
                        else ans = max(m4.a + m4.b, ans);
                    }
                }
        }
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << setprecision(17);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}