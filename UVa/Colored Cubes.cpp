/**
 * UVa1352
 * 彩⾊⽴⽅体
 */

#include <iostream>
#include <string>
#include <map>
using namespace std;

#define N 6
short c[N][6], p[24][6], cc[N], s[N] = {0}, n, m, ans;

void build() {
    short r[] = {1,5,1,1,0,4}, u[] = {2,2,5,0,2,2}, v[6], x;
    for (short i=0, t=0; i<6; ++i) {
        v[0] = i; v[1] = r[i]; v[2] = u[i]; v[3] = 5-u[i]; v[4] = 5-r[i]; v[5] = 5-i;
        for (short j=0; j<4; ++j, ++t) {
            p[t][0] = v[0]; p[t][1] = v[1]; p[t][2] = v[2]; p[t][3] = v[3]; p[t][4] = v[4]; p[t][5] = v[5];
            x = v[1]; v[1] = v[3]; v[3] = v[4]; v[4] = v[2]; v[2] = x;
        }
    }
}

void dfs(short i = 1) {
    if (i >= n) {
        short t = 0;
        for (short j=0; j<6; ++j) {
            short a[N] = {0}, x = 0;
            for (short k=0; k<n; ++k) cc[k] = c[k][p[s[k]][j]];
            for (short k=0; k<n; ++k) for (short l=k; l<n; ++l) if (cc[l] == cc[k]) ++a[k];
            for (short k=0; k<n; ++k) x = max(x, a[k]);
            t += n-x;
        }
        ans = min(ans, t);
        return;
    }
    for (short j=0; j<24; ++j) s[i] = j, dfs(i+1);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    build();
    while (cin>>n && n) {
        string s; map<string, short> id; m = 0; ans = 6*n;
        for (short i=0; i<n; ++i) for (short j=0; j<6; ++j) {
            cin >> s;
            c[i][j] = id.count(s) ? id[s] : id[s] = m++;
        }
        dfs();
        cout << ans << endl;
    }
    return 0;
}