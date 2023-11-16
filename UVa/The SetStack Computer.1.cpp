/**
 * UVa12096/LA3634
 * NWERC 2006
 */

#include <iostream>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

#define N 2010
set<int> s[N]; int stack[N], top, t; char op[10];

#define id(x) ids.count(x) ? ids[x] : (s[++t] = x, ids[x] = t)

void solve() {
    top = -1; t = 0; map<set<int>, int> ids; ids[s[0]] = 0;
    int n; cin >> n;
    while (n--) {
        cin >> op;
        if (op[0] == 'P') {
            stack[++top] = 0; cout << 0 << endl;
        } else if (op[0] == 'D') {
            int v = stack[top]; stack[++top] = v;
            cout << s[v].size() << endl;
        } else if (op[0] == 'U') {
            const set<int> &a = s[stack[top--]], &b = s[stack[top--]]; set<int> x;
            set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(x,x.begin()));
            stack[++top] = id(x);
            cout << x.size() << endl;
        } else if (op[0] == 'I') {
            const set<int> &a = s[stack[top--]], &b = s[stack[top--]]; set<int> x;
            set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(x,x.begin()));
            stack[++top] = id(x);
            cout << x.size() << endl;
        } else {
            const set<int> &a = s[stack[top--]]; set<int> x = s[stack[top--]];
            x.insert(id(a));
            stack[++top] = id(x);
            cout << x.size() << endl;
        }
    }
    cout << "***" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}