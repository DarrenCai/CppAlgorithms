/**
 * UVa10723
 * 电子人的基因
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 32
char s1[N], s2[N]; short d[N][N], n1, n2; long long c[N][N];

long long get(short i=0, short j=0) {
    long long &ref = c[i][j];
    if (ref > 0) return ref;
    if (i==n1 || j==n2) return ref = 1ll;
    if (s1[i] == s2[j]) return ref = get(i+1, j+1);
    if (d[i+1][j] < d[i][j+1]) return ref = get(i+1, j);
    if (d[i+1][j] > d[i][j+1]) return ref = get(i, j+1);
    return ref = get(i+1, j) + get(i, j+1);
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t; cin.getline(s1, N);
    for (short kase=1; kase <= t; ++kase) {
        cin.getline(s1, N); cin.getline(s2, N);
        n1 = strlen(s1); n2 = strlen(s2);
        memset(d, N, sizeof(d)); memset(c, 0, sizeof(c));
        d[n1][n2] = 0; d[n1-1][n2] = 1; d[n1][n2-1] = 1;
        for (short i=n1-1; i>=0; --i) d[i][n2] = n1-i;
        for (short i=n2-1; i>=0; --i) d[n1][i] = n2-i;
        for (short i=n1-1; i>=0; --i) for (short j=n2-1; j>=0; --j) {
            if (s1[i] == s2[j]) d[i][j] = 1+d[i+1][j+1];
            else d[i][j] = min(1+d[i+1][j], 1+d[i][j+1]);
        }
        cout << "Case #" << kase <<": " << d[0][0] << " " << get() << endl;
    }
    return 0;
}