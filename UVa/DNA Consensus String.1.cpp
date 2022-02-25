#include <iostream>
using namespace std;

#define M 52
#define N 1010
char s[M][N], ss[N], d[]="ACGT"; short c[4], x;

short conv(char c) {
    for (short i=0; i<4; ++i) if (c == d[i]) return i;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        short m, n; int cc = 0; cin >> m >> n; ss[n] = 0;
        for (short i=0; i<m; ++i) cin >> s[i];
        for (int i=0; i<n; ++i) {
            c[0] = c[1] = c[2] = c[3] = 0; x = 0;
            for (short j=0; j<m; ++j) ++c[conv(s[j][i])];
            for (short j=1; j<4; ++j) if (c[j] > c[x]) x = j;
            cc += m-c[x]; ss[i] = d[x];
        }
        cout << ss << endl << cc << endl;
    }
    return 0;
}