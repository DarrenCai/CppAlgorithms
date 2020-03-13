/**
 * UVa11584
 * 划分成回文串
 */

#include <iostream>
#include <cstring>
using namespace std;

#define min(a, b) (a<b ? a:b)
#define N 1010
char s[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        cin >> s;
        bool p[N][N] = {0}; int n = strlen(s), d[N] = {0};
        for (int l=0; l<n; ++l) for (int i=0; i+l < n; ++i) if (s[i] == s[i+l])
            p[i][l] = l<2 ? true : p[i+1][l-2];
        for (int i=n-1; i>=0; --i) {
            d[i] = N;
            for (int l=0; i+l < n; ++l) if (p[i][l]) d[i] = min(d[i], d[i+l+1] + 1);
        }
        cout << d[0] << endl;
    }
    return 0;
}