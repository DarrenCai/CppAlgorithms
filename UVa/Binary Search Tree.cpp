/**
 * UVa1264/LA4847
 * Daejon 2010
 */

#include <iostream>
using namespace std;

#define M 9999991
#define N 21
int ch[N][2], s[N]={0}, v[N]={1}, n; long long c[N][N];

void solve() {
    cin >> n;
    cin >> v[1]; ch[1][0] = ch[1][1] = 0; s[1] = 1;
    for (int i=2; i<=n; ++i) {
        cin >> v[i]; ch[i][0] = ch[i][1] = 0; s[i] = 1;
        for (int r=1; ++s[r];)
            if (v[i] < v[r]) {
                if (!ch[r][0]) {
                    ch[r][0] = i;
                    break;
                }
                r = ch[r][0];
            } else {
                if (!ch[r][1]) {
                    ch[r][1] = i;
                    break;
                }
                r = ch[r][1];
            }
    }
    for (int i=n; i>0; --i) v[i] = c[s[i]-1][s[ch[i][0]]] * v[ch[i][0]] % M * v[ch[i][1]] % M;
    cout << v[1] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    c[0][0] = 1;
    for (int i=1; i<N; ++i) {
        c[i][0] = c[i][i] = 1;
        for (int j=1; j<i; ++j) c[i][j] = (c[i-1][j] + c[i-1][j-1]) % M;
    }
    int t; cin >> t;
    while (t--) solve();
    return 0;
}