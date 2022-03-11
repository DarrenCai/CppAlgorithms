/**
 * UVa1344
 * ⽥忌赛马
 */

#include <iostream>
#include <functional>
#include <set>
using namespace std;

short solve(short n) {
    multiset<short> a; multiset<short, greater<short> > b;
    short w = 0, x;
    for (short i=0; i<n; ++i) cin >> x, a.insert(x);
    for (short i=0; i<n; ++i) cin >> x, b.insert(x);
    multiset<short, greater<short> >::iterator it = b.begin();
    while (it != b.end()) {
        multiset<short>::iterator it1 = a.upper_bound(*it);
        it1 != a.end() ? (a.erase(it1), ++w, it = b.erase(it)) : ++it;
    }
    for (it = b.begin(); it != b.end(); ++it) {
        multiset<short>::iterator it1 = a.lower_bound(*it);
        if (it1 != a.end()) a.erase(it1);
        else --w;
    }
    return w;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    short n;
    while (cin>>n && n) cout << 200*solve(n) << endl;
    return 0;
}