/**
 * UVa11520
 * 填充正⽅形
 */

#include <iostream>
using namespace std;

#define N 15
char s[N][N]; short n;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) {
        cin >> n;
        for (short i=0; i<n; ++i) cin >> s[i];
        for (short c=0; c<n; ++c) for (short r=0; r<n; ++r) if (s[r][c] == '.') for (char ch='A'; ch<='Z'; ++ch)
            if ((r==0 || s[r-1][c]!=ch) && (r+1==n || s[r+1][c]!=ch) &&
                (c==0 || s[r][c-1]!=ch) && (c+1==n || s[r][c+1]!=ch)) {
                s[r][c] = ch;
                break;
            }
        cout << "Case " << kase << ':' << endl;
        for (short i=0; i<n; ++i) cout << s[i] << endl;
    }
    return 0;
}