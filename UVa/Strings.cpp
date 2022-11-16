/**
 * UVa11081
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 10007
#define N 63
char s1[N], s2[N], s3[N]; int d[N][N][2];

void solve() {
    cin >> s1+1 >> s2+1 >> s3+1;
    int a = strlen(s1+1), b = strlen(s2+1), c = strlen(s3+1);
    for (int i=1; i<=c; ++i) {
        for (int j=a; j>0; --j) for (int k=b; k>0; --k) {
            d[j][k][0] = s1[j]==s3[i] ? (i==1 ? 1 : d[j-1][k][0] + d[j-1][k][1]) : 0;
            d[j][k][1] = s2[k]==s3[i] ? (i==1 ? 1 : d[j][k-1][0] + d[j][k-1][1]) : 0;
        }
        for (int j=a; j>0; --j)
            d[j][0][0] = s1[j]==s3[i] ? (i==1 ? 1 : d[j-1][0][0] + d[j-1][0][1]) : 0;
        for (int j=1; j<=a; ++j) d[j][0][0] = (d[j][0][0] + d[j-1][0][0]) % M;
        for (int j=b; j>0; --j)
            d[0][j][1] = s2[j]==s3[i] ? (i==1 ? 1 : d[0][j-1][0] + d[0][j-1][1]) : 0;
        for (int j=1; j<=b; ++j) d[0][j][1] = (d[0][j][1] + d[0][j-1][1]) % M;
        for (int j=1; j<=a; ++j) for (int k=1; k<=b; ++k) {
            d[j][k][0] = (d[j][k][0] + d[j-1][k][0]) % M;
            d[j][k][1] = (d[j][k][1] + d[j][k-1][1]) % M;
        }
    }
    cout << (d[a][b][0] + d[a][b][1]) % M << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=0; i<N; ++i) d[0][i][0] = d[i][0][1] = 0;
    short t; cin >> t;
    while (t--) solve();
    return 0;
}