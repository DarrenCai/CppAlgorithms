/**
 * UVa12545
 * 比特变换器
 */

#include <iostream>
#include <string>
using namespace std;

#define max(a,b) (a>b ? a:b)

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short c; cin >> c; string s, t;
    for (short k=1; k<=c; ++k) {
        cin >> s >> t;
        short n = s.length(), s1 = 0, t1 = 0, n0 = 0, n1 = 0, nz = 0;
        for (short i=0; i<n; ++i) {
            if (s[i] == '?') {
                ++nz;
            } else if (s[i] == '1') {
                ++s1;
                if (t[i] != s[i]) ++n1;
            } else if (t[i] != s[i]) ++n0;
            if (t[i] == '1') ++t1;
        }
        if (s1>t1 || n1+s1>n) cout << "Case " << k << ": -1" << endl;
        else {
            cout << "Case " << k << ": " << nz + max(n1, n0) << endl;
        }
    }
    return 0;
}