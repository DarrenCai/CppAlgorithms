/**
 * UVa11136
 * 促销活动
 */

#include <iostream>
#include <set>
using namespace std;

int n;

void solve() {
    multiset<int, greater<int> > s1; multiset<int> s2; bool f = true; long long ans = 0;
    for (int i=n; i>0; --i) {
        int k, x; cin >> k;
        while (k--) {
            cin >> x;
            if (f) {
                s2.insert(x);
                if (s2.size() == i<<1) {
                    for (int j=0; j<i; ++j) s1.insert(*s2.begin()), s2.erase(s2.begin());
                    f = false;
                }
            } else if (x < *s1.begin()) s1.erase(s1.begin()), s1.insert(x);
            else if (x > *s2.begin()) s2.erase(s2.begin()), s2.insert(x);
        }
        if (f) {
            multiset<int>::iterator it1 = s2.begin(), it2 = --s2.end();
            ans += *it2 - *it1;
            s2.erase(it1); s2.erase(it2);
        } else {
            multiset<int, greater<int> >::iterator it1 = --s1.end(); multiset<int>::iterator it2 = --s2.end();
            ans += *it2 - *it1;
            s1.erase(it1); s2.erase(it2);
        }
    }
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n && n) solve();
    return 0;
}