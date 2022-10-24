/**
 * UVa1375/LA3623
 * 给孩子起名
 * Asia Japan 2006 in Yokohama
 */

#include <iostream>
#include <string>
using namespace std;

#define N 55
#define M 15
#define L 25

string d0[N][L], d[N][M][L];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n, l; string s[N];
    while (cin >> n >> l && n) {
        for (short i=0; i<n; ++i) cin >> s[i];
        bool start[N] = {false};
        for (short i=0; i<n; ++i) for (short j=s[i].length()-1; j>1; --j) if (s[i][j] <= 'Z') {
            start[i] = true; break;
        }
        for (short i=0; i<26; ++i) for (short j=0; j<=l; ++j) d0[i][j] = "~";
        for (short i=0; i<n; ++i) for (short j=0; j<=l; ++j) {
            short k = s[i].length();
            d[i][k][j] = j==0 ? "" : "~";
            while (--k > 1) d[i][k][j] = "~";
        }
        for (short i=0; i<n; ++i) if (!start[i]) {
            string v = s[i].substr(2); short ii = s[i][0]-'A';
            if (v < d0[ii][v.length()]) d0[ii][v.length()] = v;
            if (v < d[i][2][v.length()]) d[i][2][v.length()] = v;
        }
        for (short i=0; i<=l; ++i) {
            for (short j=0; j<n; ++j) {
                bool updated = false;
                for (short k=s[j].length()-1; k>1; --k) {
                    if (s[j][k] <= 'Z') {
                        short ii = s[j][k] - 'A';
                        for (short ll=0; ll<=i; ++ll) if (d0[ii][ll] < "~" && d[j][k+1][i-ll] < "~") {
                            string ss = d0[ii][ll] + d[j][k+1][i-ll];
                            if (ss < d[j][k][i]) d[j][k][i] = ss;
                            short iii = s[j][0] - 'A';
                            if (k==2 && ss < d0[iii][i]) d0[iii][i] = ss, updated = true;
                        }
                    } else if (i>0 && d[j][k+1][i-1] < "~") {
                        string ss = s[j][k] + d[j][k+1][i-1];
                        if (ss < d[j][k][i]) d[j][k][i] = ss;
                        short ii = s[j][0] - 'A';
                        if (k==2 && ss < d0[ii][i]) d0[ii][i] = ss, updated = true;
                    }
                }
                while(updated) {
                    updated = false;
                    for (short jj=0; jj<=j; ++jj) {
                        for (short k=s[jj].length()-1; k>1; --k) {
                            if (s[jj][k] <= 'Z') {
                                short ii = s[jj][k] - 'A';
                                for (short ll=0; ll<=i; ++ll) if (d0[ii][ll] < "~" && d[jj][k+1][i-ll] < "~") {
                                    string ss = d0[ii][ll] + d[jj][k+1][i-ll];
                                    if (ss < d[jj][k][i]) d[jj][k][i] = ss;
                                    short iii = s[jj][0] - 'A';
                                    if (k==2 && ss < d0[iii][i]) d0[iii][i] = ss, updated = true;
                                }
                            } else if (i>0 && d[jj][k+1][i-1] < "~") {
                                string ss = s[jj][k] + d[jj][k+1][i-1];
                                if (ss < d[jj][k][i]) d[jj][k][i] = ss;
                                short ii = s[jj][0] - 'A';
                                if (k==2 && ss < d0[ii][i]) d0[ii][i] = ss, updated = true;
                            }
                        }
                    }
                }
            }
        }
        string ans = d0[18][l];
        cout << (ans == "~" ? "-" : ans) << endl;
    }
    return 0;
}