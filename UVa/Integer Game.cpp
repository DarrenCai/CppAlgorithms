/**
 * UVa11489
 * 整数游戏
 */

#include <iostream>
using namespace std;

char s[1010];

bool solve() {
    cin >> s;
    int c[3] = {0}, r = 0;
    for (int i=0; s[i]; ++i) {
        int x = (s[i]-'0') % 3;
        ++ c[x]; r += x;
    }
    r %= 3;
    return (r==0 && c[0]&1) || (r==1 && c[1] && ~c[0]&1) || (r==2 && c[2] && ~c[0]&1);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Case " << kase << ": " << (solve() ? 'S' : 'T') << endl;
    return 0;
}