/**
 * UVa10763
 * 交换学生
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 500200
struct node {
    int a, b; bool f;
    node(){}
    node(int m, int n) {
        f = m<n;
        a = min(m, n);
        b = max(m, n);
    }
    bool operator< (const node& rhs) const {
        return a<rhs.a || (a==rhs.a && b<rhs.b);
    }
} s[N];
int n;


bool solve() {
    for (int i=0; i<n; ++i) {
        int a, b; cin >> a>> b;
        s[i] = node(a, b);
    }
    sort(s, s+n);
    int c = s[0].f ? 1 : -1;
    for (int k=0, i=1; i<n; ++i) {
        if (s[i].a!=s[k].a || s[i].b!=s[k].b) {
            if (c) return false;
            k = i;
        }
        s[i].f ? ++c : --c;
    }
    return !c;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n && n) cout << (solve() ? "YES" : "NO") << endl;
    return 0;
}