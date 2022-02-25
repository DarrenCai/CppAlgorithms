/**
 * UVa10340
 * 子序列
 */

#include <iostream>
#include <string>
using namespace std;

string s, t;

bool check() {
    int m = s.size(), n = t.size(), cur = -1;
    if (m > n) return false;
    for (int i=0; i<m; ++i) {
        while (cur < n && t[++cur] != s[i]);
        if (cur >= n) return false;
    }
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while(cin >> s >> t) cout << (check() ? "Yes" : "No") << endl;
    return 0;
}