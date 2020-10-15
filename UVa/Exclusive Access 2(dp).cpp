/**
 * UVa1439
 * 独占访问2
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 20
#define M 200
short e[M][2], a[N], c[N], n, d[1<<N]={0}; int ans[1<<N]; bool g[N][N], v[N], check[1<<N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short m;
    while (cin >> m) {
        n=0; memset(g, 0, sizeof(g)); memset(v, 0, sizeof(v)); memset(check, 0, sizeof(check));
        for (short i=0; i<m; ++i) {
            char c1, c2; cin >> c1 >> c2; c1 -= 'L'; c2 -= 'L';
            if (!v[c1]) a[n++] = c1, v[c1] = true;
            if (!v[c2]) a[n++] = c2, v[c2] = true;
            g[c1][c2] = g[c2][c1] = true;
            e[i][0] = c1; e[i][1] = c2;
        }
        const int ss = (1<<n)-1;
        for (int s=1, nn; s<=ss; ++s) if (!check[s]) {
            for (nn=0; (1<<nn) <= s; ++nn);
            for (int i=0; i<nn && !check[s]; ++i) if (s&(1<<i))
                for (int j=i+1; j<nn && !check[s]; ++j) if (s&(1<<j) && g[a[i]][a[j]]) check[s] = true;
            if (check[s]) for (int i=0; i<n; ++i) check[s | (1<<i)] = true;
        }
        for (int s=1; s<=ss; ++s) {
            d[s] = N;
            for (int sub=s; sub; sub = (sub-1)&s) if (!check[sub] && d[s^sub]+1 < d[s]) {
                d[s] = d[s^sub] + 1; ans[s] = sub;
            }
        }
        for (int color=1, s=ss; s; s ^= ans[s], ++color)
            for (int i=0; i<n; ++i) if ((1<<i) & ans[s]) c[a[i]] = color;
        cout << d[ss]-2 << endl;
        for (short i=0; i<m; ++i) {
            char c1 = 'L'+e[i][0], c2 = 'L'+e[i][1]; bool less = c[e[i][0]] < c[e[i][1]];
            cout << (less ? c1 : c2) << ' ' << (less ? c2 : c1) << endl;
        }
    }
    return 0;
}