/**
 * UVa11166
 * 带符号二进制
 */

#include <iostream>
using namespace std;

#define N 50010
char s[N]; int n, m;
struct {int n; char s;} d[N][4];

void print(short p) {
    if (p==1 || p==2) cout << '+';
    for (int i=0; i<=m; ++i) {
        cout << (p==0 ? '+' : (p==1 ? '-' : '0'));
        if (p==0 || p==3) {
            p = (s[i]=='1' || p==3) ? (d[i][p].s == '0' ? 3 : 0) : (d[i][p].s == '0' ? 2 : 1);
        } else {
            if (p==1) p = s[i]=='0' ? (d[i][p].s == '0' ? 2 : 1) : (d[i][p].s == '0' ? 3 : 0);
            else p = d[i][p].s == '0' ? 2 : 1;
        }
    }
    if (p==1) cout << '-';
    for (int i=m+1; i<n; ++i) cout << '0';
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>s && s[0]!='0') {
        for (n=0; s[n]; ++n) if (s[n] =='1') m=n;
        d[m][0].n = d[m][1].n = 1; d[m][2].n = d[m][3].n = N;
        for (int i=m-1; i>=0; --i)
            if (s[i] == '1') {
                if (d[i+1][0].n <= d[i+1][3].n) {
                    d[i][0].n = d[i][1].n = 1 + d[i+1][0].n;
                    d[i][0].s = d[i][1].s = '+';
                } else {
                    d[i][0].n = d[i][1].n = 1 + d[i+1][3].n;
                    d[i][0].s = d[i][1].s = '0';
                }
                if (d[i+1][1].n <= d[i+1][2].n) {
                    d[i][2].n = d[i+1][1].n;
                    d[i][2].s = '-';
                } else {
                    d[i][2].n = d[i+1][2].n;
                    d[i][2].s = '0';
                }
                d[i][3].n = N;
            } else {
                if (d[i+1][1].n <= d[i+1][2].n) {
                    d[i][0].n = d[i][1].n = 1 + d[i+1][1].n;
                    d[i][0].s = d[i][1].s = '-';
                } else {
                    d[i][0].n = d[i][1].n = 1 + d[i+1][2].n;
                    d[i][0].s = d[i][1].s = '0';
                }
                d[i][2].n = N;
                if (d[i+1][0].n <= d[i+1][3].n) {
                    d[i][3].n = d[i+1][0].n;
                    d[i][3].s = '+';
                } else {
                    d[i][3].n = d[i+1][3].n;
                    d[i][3].s = '0';
                }
            }
        if (d[0][0].n <= min(d[0][1].n, d[0][2].n)) print(0);
        else if (d[0][0].n == 1 + min(d[0][1].n, d[0][2].n)) {
            if (m == 0 || d[0][0].s == '+') print(0);
            else d[0][0].n == 1 + d[0][1].n ? print(1) : (s[2]=='1' ? print(0) : print(2));
        } else d[0][1].n < d[0][2].n ? print(1) : print(2);
    }
    return 0;
}