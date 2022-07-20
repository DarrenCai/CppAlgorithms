/**
 * UVa10391
 * 复合词
 * Waterloo local 2011
 */

#include <iostream>
#include <string>
#include <set>
using namespace std;

#define N 120200
string s[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int n = 0; set<string> ss;
    while (cin >> s[n]) ss.insert(s[n++]);
    for (int i=0; i<n; ++i) for (int j=1, c=s[i].size(); j<c; ++j)
        if (ss.count(s[i].substr(0, j)) && ss.count(s[i].substr(j))) {
            cout << s[i] << endl;
            break;
        }
    return 0;
}