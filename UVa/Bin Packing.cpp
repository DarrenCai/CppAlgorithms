/**
 * UVa1149
 * 装箱
 */

#include <iostream>
#include <functional>
#include <set>
using namespace std;
multiset<short, greater<short> > s;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short k; cin>>k;
    while (k--) {
        int n, c = 0; short l; cin >> n >> l;
        while (n--) {short v; cin>>v; s.insert(v);}
        while (!s.empty()) {
            short v = l - *s.begin();
            s.erase(s.begin());
            multiset<short, greater<short> >::iterator it = s.lower_bound(v);
            if (it != s.end()) s.erase(it);
            ++ c;
        }
        cout << c << endl;
        if (k) cout << endl;
    }
    return 0;
}