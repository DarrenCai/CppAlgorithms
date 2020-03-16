/**
 * UVa1625
 * 颜色的长度
 */

#include <iostream>
#include <cstring>
using namespace std;

#define min(a, b) (a<b ? a:b)
#define N 5010
char s1[N], s2[N];
int d[N][N] = {0}, p1[26], p2[26];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        cin >> s1 >> s2;
        const int m = strlen(s1), n = strlen(s2);
        memset(p1, -1, sizeof(p1)); memset(p2, -1, sizeof(p2));
        for (int i=0; i<m; ++i) s1[i] -= 'A', p1[s1[i]] = i;
        for (int i=0; i<n; ++i) s2[i] -= 'A', p2[s2[i]] = i;
        bool in1[26] = {false};
        for (int i=0; i<=m; ++i) {
            if (i > 0) {
                in1[s1[i-1]] = true; int s = 0;
                for (int k=0; k<26; ++k) if (in1[k] && (i<=p1[k] || p2[k]>-1)) ++s;
                d[i][0] = d[i-1][0] + s;
            }
            bool in2[26] = {false};
            for (int j=1; j<=n; ++j) {
                in2[s2[j-1]] = true; int s = 0;
                for (int k=0; k<26; ++k) if ((in1[k] || in2[k]) && (i<=p1[k] || j<=p2[k])) ++s;
                d[i][j] = i==0 ? d[i][j-1] + s : min(d[i-1][j], d[i][j-1]) + s;
            }
        }
        cout << d[m][n] << endl;
    }
    return 0;
}