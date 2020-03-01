/**
 * UVa1624
 * 打结
 */

#include <iostream>
#include <set>
using namespace std;

#define L 1000010
struct node {
    int o: 28;
    int f: 1;
    node(){}
    node(int o, int f):o(o),f(f){}
} over[L];

int l, p;
set<int> s;

bool adj(const set<int>::iterator& it1, const set<int>::iterator& it2) {
    set<int>::iterator it = it1;
    if (it == s.begin()) return ++it == it2 || *s.rbegin() == *it2;
    if (*it == *s.rbegin()) return --it == it2 || s.begin() == it2;
    return ++it == it2 || --(it=it1) == it2;
}

bool op(set<int>::iterator& it) {
    if (it == s.end()) return false;
    int a = *it, b = over[a].o; set<int>::iterator it1 = s.find(b);
    if (adj(it, it1)) {
        s.erase(it); it = s.erase(it1); op(it); return true;
    }
    set<int>::iterator it2 = it;
    if (++it2 != s.end() && over[*it2].f == over[a].f) {
        set<int>::iterator it3 = s.find(over[*it2].o);
        if (adj(it1, it3)) {
            s.erase(it); it = s.erase(it2);
            if (it == it1 || it == it3) {
                s.erase(it1); it = s.erase(it3);
            } else {
                s.erase(it1); s.erase(it3);
            }
            op(it); return true;
        }
    }
    return false;
}

bool judge() {
    while (!s.empty()) {
        const int size = s.size();
        for (set<int>::iterator it = s.begin(); it != s.end(); ++it) if (op(it)) break;
        if (size == s.size()) return false;
    }
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) {
        cin >> l >> p; s.clear();
        for (int i=0; i<p; ++i) {
            int a, b; cin >> a >> b;
            s.insert(a); s.insert(b);
            over[a]=node(b,1); over[b]=node(a,0);
        }
        cout << "Case #" << k << ": " << (judge() ? "YES" : "NO") << endl;
    }
    return 0;
}