/**
 * UVa12117/LA4058
 * ACM谜题
 * Dhaka 2007
 */

#include <iostream>
using namespace std;

#define M 1000000000000
#define N 2001
const int t[][7][3] = {
    {{0, 0, 1}, {1, 5, 2}, {5, 8, 2}, {11, 1, 2}, {13, 3, 2}, {17, 4, 2}, {21, 2, 2}},
    {{18, 0, 1}, {20, 4, 2}},
    {{14, 0, 1}, {19, 3, 2}},
    {{3, 0, 1}, {9, 1, 1}, {15, 6, 2}},
    {{10, 2, 1}, {12, 0, 1}, {16, 7, 2}},
    {{2, 0, 1}},
    {{7, 1, 1}},
    {{8, 2, 1}},
    {{4, 5, 2}, {6, 0, 1}}
}, c[] = {7, 2, 2, 3, 3, 1, 1, 1, 2};
long long e[N][9] = {0}; int n, kase = 0;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    e[0][0] = 1;
    for (int i=0; i<N; ++i) for (int j=0; j<9; ++j) if (e[i][j]) for (int k=0; k<c[j]; ++k) if (i+t[j][k][2] < N) {
        int ii = i+t[j][k][2], jj = t[j][k][1];
        e[ii][jj] = (e[ii][jj] + e[i][j]) % M;
    }
    while (cin >> n && n) cout << "Case " << ++kase << ": " << e[n][0] << endl;
    return 0;
}