/**
 * UVa10340
 * 8皇后问题
 */

#include <iostream>
#include <cstdio>
using namespace std;

short a[9], r, c, t;
void printNewCase() {
    ++ t;
    if (t<10) cout << ' ';
    cout << t << "     ";
    for (short j=1; j<9; ++j)
        cout << ' ' << a[j];
    cout << endl;
}
void solve(short cur) {
    if (cur == c) {
        if (c < 8) solve(c+1);
        else printNewCase();
    } else for (short i=1; i<9; ++i) {
        if (i==r) continue;
        bool ok = true;
        for (short j=1; j<cur && ok; ++j)
            if (a[j]==i || a[j]-i == cur-j || a[j]-i == j-cur) ok = false;
        if (cur < c && (a[c]==i || a[c]-i == cur-c || a[c]-i == c-cur)) ok = false;
        if (ok) {
            a[cur] = i;
            if (cur == 8) {
                printNewCase();
            } else solve(cur+1);
        }
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("ou.txt", "w", stdout);
    int k; cin>>k;
    while (k--) {
        cout << "SOLN       COLUMN" << endl << " #      1 2 3 4 5 6 7 8" << endl << endl;
        cin >> r >> c; a[c] = r; t=0;
        solve(1);
        if (k) cout << endl;
    }
    return 0;
}