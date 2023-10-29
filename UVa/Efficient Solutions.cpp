/**
 * UVa11020
 * 优势人群
 */

#include <iostream>
#include <set>
using namespace std;

struct node {
    int x, y;
    bool operator< (const node& rhs) const {
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }
} t;

void solve(int kase) {
    if (kase > 1) cout << endl;
    cout << "Case #" << kase << ':' << endl;
    multiset<node> s;
    int n; cin >> n;
    while (n--) {
        cin >> t.x >> t.y;
        multiset<node>::iterator it = s.lower_bound(t);
        if(it == s.begin() || (--it)->y > t.y) {
            s.insert(t);
            it = s.upper_bound(t);
            while(it != s.end() && it->y >= t.y) s.erase(it++);
        }
        cout << s.size() << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) solve(kase);
    return 0;
}