/**
 * UVa1030
 * ⽴⽅体成像
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 15
char c[6][N][N]; short p[6][N][N], n; bool cc[N][N][N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin >> n && n) {
        memset(p, -1, sizeof(p)); memset(cc, 0, sizeof(cc)); const short m = n-1; short ans = n*n*n;
        for (short i=0; i<n; ++i) {
            cin >> c[0][i] >> c[1][i] >> c[2][i] >> c[3][i] >> c[4][i] >> c[5][i];
            for (short j=0; j<n; ++j) if (c[0][i][j] == '.') for (short k=0; k<n; ++k) cc[k][j][i] = true;
            for (short j=0; j<n; ++j) if (c[1][i][j] == '.') for (short k=0; k<n; ++k) cc[j][k][i] = true;
            for (short j=0; j<n; ++j) if (c[2][i][j] == '.') for (short k=0; k<n; ++k) cc[k][m-j][i] = true;
            for (short j=0; j<n; ++j) if (c[3][i][j] == '.') for (short k=0; k<n; ++k) cc[m-j][k][i] = true;
            for (short j=0; j<n; ++j) if (c[4][i][j] == '.') for (short k=0; k<n; ++k) cc[i][j][k] = true;
            for (short j=0; j<n; ++j) if (c[5][i][j] == '.') for (short k=0; k<n; ++k) cc[m-i][j][k] = true;
        }
        while (true) {
            bool f = false;
            for (short i=0; i<n; ++i) for (short j=0; j<n; ++j) {
                if (c[0][i][j] != '.') {
                    short &r = p[0][i][j]; while (cc[m-r-1][j][i]) ++r;
                    short k = m-r-1, &p1 = p[1][i][k], &p3 = p[3][i][m-k], &p4 = p[4][k][j], &p5 = p[5][m-k][j];
                    while (cc[k][p1+1][i]) ++p1; while (cc[k][m-p3-1][i]) ++p3;
                    while (cc[k][j][p4+1]) ++p4; while (cc[k][j][m-p5-1]) ++p5;
                    char &c0 = c[0][i][j], &c1 = c[1][i][k], &c3 = c[3][i][m-k], &c4 = c[4][k][j], &c5 = c[5][m-k][j];
                    if ((p1+1==j && c1!=c0) || (p3+1==m-j && c3!=c0) || (p4+1==i && c4!=c0) || (p5+1==m-i && c5!=c0))
                        cc[k][j][i] = f = true;
                }
                if (c[1][i][j] != '.') {
                    short &r = p[1][i][j]; while (cc[j][r+1][i]) ++r;
                    short k = r+1, &p0 = p[0][i][k], &p2 = p[2][i][m-k], &p4 = p[4][j][k], &p5 = p[5][m-j][k];
                    while (cc[m-p0-1][k][i]) ++p0; while (cc[p2+1][k][i]) ++p2;
                    while (cc[j][k][p4+1]) ++p4; while (cc[j][k][m-p5-1]) ++p5;
                    char &c0 = c[0][i][k], &c1 = c[1][i][j], &c2 = c[2][i][m-k], &c4 = c[4][j][k], &c5 = c[5][m-j][k];
                    if ((p0+1==m-j && c0!=c1) || (p2+1==j && c2!=c1) || (p4+1==i && c4!=c1) || (p5+1==m-i && c5!=c1))
                        cc[j][k][i] = f = true;
                }
                if (c[2][i][j] != '.') {
                    short &r = p[2][i][j]; while (cc[r+1][m-j][i]) ++r;
                    short k = r+1, &p1 = p[1][i][k], &p3 = p[3][i][m-k], &p4 = p[4][k][m-j], &p5 = p[5][m-k][m-j];
                    while (cc[k][p1+1][i]) ++p1; while (cc[k][m-p3-1][i]) ++p3;
                    while (cc[k][m-j][p4+1]) ++p4; while (cc[k][m-j][m-p5-1]) ++p5;
                    char &c1 = c[1][i][k], &c2 = c[2][i][j], &c3 = c[3][i][m-k], &c4 = c[4][k][m-j], &c5 = c[5][m-k][m-j];
                    if ((p1+1==m-j && c1!=c2) || (p3+1==j && c3!=c2) || (p4+1==i && c4!=c2) || (p5+1==m-i && c5!=c2))
                        cc[k][m-j][i] = f = true;
                }
                if (c[3][i][j] != '.') {
                    short &r = p[3][i][j]; while (cc[m-j][m-r-1][i]) ++r;
                    short k = m-r-1, &p0 = p[0][i][k], &p2 = p[2][i][m-k], &p4 = p[4][m-j][k], &p5 = p[5][j][k];
                    while (cc[m-p0-1][k][i]) ++p0; while (cc[p2+1][k][i]) ++p2;
                    while (cc[m-j][k][p4+1]) ++p4; while (cc[m-j][k][m-p5-1]) ++p5;
                    char &c0 = c[0][i][k], &c2 = c[2][i][m-k], &c3 = c[3][i][j], &c4 = c[4][m-j][k], &c5 = c[5][j][k];
                    if ((p0+1==j && c0!=c3) || (p2+1==m-j && c2!=c3) || (p4+1==i && c4!=c3) || (p5+1==m-i && c5!=c3))
                        cc[m-j][k][i] = f = true;
                }
                if (c[4][i][j] != '.') {
                    short &r = p[4][i][j]; while (cc[i][j][r+1]) ++r;
                    short k = r+1, &p0 = p[0][k][j], &p1 = p[1][k][i], &p2 = p[2][k][m-j], &p3 = p[3][k][m-i];
                    while (cc[m-p0-1][j][k]) ++p0; while (cc[i][p1+1][k]) ++p1;
                    while (cc[p2+1][j][k]) ++p2; while (cc[i][m-p3-1][k]) ++p3;
                    char &c0 = c[0][k][j], &c1 = c[1][k][i], &c2 = c[2][k][m-j], &c3 = c[3][k][m-i], &c4 = c[4][i][j];
                    if ((p0+1==m-i && c0!=c4) || (p1+1==j && c1!=c4) || (p2+1==i && c2!=c4) || (p3+1==m-j && c3!=c4))
                        cc[i][j][k] = f = true;
                }
                if (c[5][i][j] != '.') {
                    short &r = p[5][i][j]; while (cc[m-i][j][m-r-1]) ++r;
                    short k = m-r-1, &p0 = p[0][k][j], &p1 = p[1][k][m-i], &p2 = p[2][k][m-j], &p3 = p[3][k][i];
                    while (cc[m-p0-1][j][k]) ++p0; while (cc[m-i][p1+1][k]) ++p1;
                    while (cc[p2+1][j][k]) ++p2; while (cc[m-i][m-p3-1][k]) ++p3;
                    char &c0 = c[0][k][j], &c1 = c[1][k][m-i], &c2 = c[2][k][m-j], &c3 = c[3][k][i], &c5 = c[5][i][j];
                    if ((p0+1==i && c0!=c5) || (p1+1==j && c1!=c5) || (p2+1==m-i && c2!=c5) || (p3+1==m-j && c3!=c5))
                        cc[m-i][j][k] = f = true;
                }
            }
            if (!f) break;
        }
        for (short i=0; i<n; ++i) for (short j=0; j<n; ++j) for (short k=0; k<n; ++k) if (cc[i][j][k]) --ans;
        cout << "Maximum weight: " << ans << " gram(s)" << endl;
    }
    return 0;
}