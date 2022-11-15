/**
 * UVa10100
 */

#include <iostream>
#include <string>
using namespace std;

#define N 1010
char s1[N], s2[N]; int d[N][N], m, n, kase = 0;
string a[N], b[N];

bool check(char c) {
    return (c>='a' && c<='z') || (c>='0' && c<='9') || (c>='A' && c<='Z');
}

void solve() {
    if (++kase < 10) cout << ' ';
    cout << kase << ". ";
    if (s1[0] && s2[0]) {
        int x = 0, y = 0;
        for (int i=m=0; s1[i]; ++i) {
            if (!check(s1[i])) {
                if (y > x) a[++m] = string(s1+x, s1+y);
                x = i+1;
            } else y = i+1;
        }
        if (y > x) a[++m] = string(s1+x, s1+y);
        for (int i=n=x=y=0; s2[i]; ++i) {
            if (!check(s2[i])) {
                if (y > x) b[++n] = string(s2+x, s2+y);
                x = i+1;
            } else y = i+1;
        }
        if (y > x) b[++n] = string(s2+x, s2+y);
        for (int i=0; i<=m; ++i) for (int j=0; j<=n; ++j)
            d[i][j] = i && j ? (a[i]==b[j] ? 1+d[i-1][j-1] : max(d[i-1][j], d[i][j-1])) : 0;
        cout << "Length of longest match: " << d[m][n] << endl;
    } else cout << "Blank!" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin.getline(s1, N) && cin.getline(s2, N)) solve();
    return 0;
}