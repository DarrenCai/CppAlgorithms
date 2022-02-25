/**
 * UVa1339
 * 古⽼的密码
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define N 110
char s1[N], s2[N]; short c1[N], c2[N];

bool check() {
    short n = strlen(s1);
    sort(s1, s1+n); sort(s2, s2+n);
    memset(c1, 0, sizeof(c1)); memset(c2, 0, sizeof(c2));
    short n1 = 0, n2 = 0;
    if (n1 != n2) return false;
    for (short j=1; j<=n; ++j) {
        s1[j]==s1[j-1] ? ++c1[n1] : ++n1;
        s2[j]==s2[j-1] ? ++c2[n2] : ++n2;
    }
    sort(c1, c1+n1); sort(c2, c2+n1);
    for (short i=0; i<n1; ++i) if (c1[i] != c2[i]) return false;
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>s1>>s2) cout << (check() ? "YES" : "NO") << endl;
    return 0;
}