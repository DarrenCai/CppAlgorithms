/**
 * UVa12088
 * 表达式
 */

#include <iostream>
using namespace std;

#define N 210
short p[8][N], n[8], c[10]; int b[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
char s[N], d[N]; bool add[N]; 

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    for (short kase=1; kase<=t; ++kase) {
        cin >> s >> d;
        for (short i=0; i<10; ++i) c[i] = 0;
        for (short i=0; d[i]; ++i) ++c[d[i]-'0'];
        for (short i=0; i<8; ++i) n[i] = 0;
        for (short i=0; s[i]; ++i) {
            if (s[i]=='#') {
                add[i] = !(i>0 && s[i-1]=='-');
                short j=0; while (s[i+j]=='#') add[i+j] = add[i], ++j;
                for (short k=0; k<j; ++k) p[k][n[k]++] = i+j-k-1;
                i += j-1;
            }
        }
        for (short i=0; s[i]; ++i) {
            if (s[i]=='-' && s[i+1]=='(') {
                short cnt = 1, j=i+2;
                while (cnt) {
                    if (s[j] == ')') --cnt;
                    if (s[j++] == '(') ++cnt;
                }
                for (short k=i+2; k<j; ++k) add[k] = !add[k];
            }
        }
        int sum = 0;
        for (short i=7; i>=0; --i) for (short j=n[i]-1, ii; j>=0; --j) {
            if (add[ii = p[i][j]]) {
                for (short k=9; k>=0; --k) if (c[k]) {
                    --c[k];
                    sum += k*b[i];
                    s[ii] = '0'+k;
                    break;
                }
            }
        }
        for (short i=7; i>=0; --i) for (short j=0, ii; j<n[i]; ++j) {
            if (!add[ii = p[i][j]]) {
                for (short k=0; k<=9; ++k) if (c[k]) {
                    --c[k];
                    sum -= k*b[i];
                    s[ii] = '0'+k;
                    break;
                }
            }
        }
        cout << "Case " << kase << ':' << endl << s << endl << sum << endl;
    }
    return 0;
}