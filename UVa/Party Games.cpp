/**
 * UVa1610
 * 聚会游戏
 */

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

#define N 1002
#define min(a,b) (a<b ? a:b)

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n; string s[N];
    while (cin>>n && n) {
        for (short i=0; i<n; ++i) cin >> s[i];
        sort(s, s+n); n >>= 1;
        string t = ""; short l = n-1, m = min(s[l].length(), s[n].length());
        for (short i=0; i<m; ++i)
            if (s[l][i]!=s[n][i]) break;
            else t += s[l][i];
        short c = t.length(), cl = s[l].length(), cn = s[n].length();
        if (cl == c) {
            cout << t << endl;
        } else if (cl == c+1) {
            cout << s[l] << endl;
        } else if (s[l][c]+1 < s[n][c]) {
            cout << t << ++s[l][c] << endl;
        } else if (cn > c+1) {
            cout << t << s[n][c] << endl;
        } else if (cl == c+2) {
            cout << s[l] << endl;
        } else {
            cout << t << s[l][c];
            while (++c < cl && s[l][c] == 'Z') cout << s[l][c];
            if (c < cl) cout << (c==cl-1 ? s[l][c] : ++s[l][c]);
            cout << endl;
        }
    }
    return 0;
}