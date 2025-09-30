/**
 * UVa1505/LA5835
 * Fuzhou 2011
 */

#include <iostream>
#include <cstring>
using namespace std;

#define T 64
int g[T][T], r[T][T], s[T][T], c[T], d[T], e[T], f[T], n, t; bool v[T][T], v1[T], v2[T], cc[6];

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

int h(int i) {
    int s = 0;
    for (int j=0; j<6; ++j) cc[j] = false;
    for (int j=0; j<f[i]; ++j) cc[c[r[i][j]]] = true;
    for (int j=0; j<6; ++j) if (cc[j]) ++s;
    return s;
}

bool IDAStar(int step, int maxd) {
    if (step == maxd) return f[maxd] == 0;
    const int c1 = e[step], c2 = f[step], (&x)[T] = g[step], (&y)[T] = r[step];
    int n = step+1, &c3 = e[n], &c4 = f[n], (&u)[T] = g[n], (&v)[T] = r[n]; bool w[6] = {false};
    for (int i=0; i<c1; ++i) w[c[x[i]]] = true;
    for (int i=0; i<6; ++i) if (w[i]) {
        for (int j=1; j<t; ++j) v1[j] = v2[j] = false;
        for (int j=0; j<c2; ++j) v1[y[j]] = true;
        for (int j=c3=c4=0; j<c1; ++j) if (c[x[j]] == i) v1[x[j]] = false;
        for (int j=0, k; j<c1; ++j) {
            if (c[k = x[j]] != i) v2[k] = true;
            else for (int a=0; a<d[k]; ++a) if (v1[s[k][a]]) v2[s[k][a]] = true;
        }
        for (int j=1; j<t; ++j) if (v2[j]) u[c3++] = j;
        for (int j=1; j<t; ++j) if (v1[j]) v[c4++] = j;
        if (c4 < c2 && step + h(n) < maxd && IDAStar(n, maxd)) return true;
    }
    return false;
}

int solve() {
    memset(v, 0, sizeof(v));
    for (int i=0, u=0; i<n; ++i) for (int j=0; j<n; ++j, ++u) {
        cin >> d[u]; f[u] = u;
        if (j > 0 && d[u-1] == d[u]) f[u] = find(u-1);
        if (i > 0 && d[u-n] == d[u]) f[f[u]] = find(u-n);
    }
    for (int i=t=0, u=0; i<n; ++i) for (int j=0; j<n; ++j, ++u) {
        if (find(u) == u) c[t] = d[u], e[u] = t++;
        if (j > 0 && d[u-1] != d[u]) {
            int x = e[find(u)], y = e[find(u-1)]; v[x][y] = v[y][x] = true;
        }
        if (i > 0 && d[u-n] != d[u]) {
            int x = e[find(u)], y = e[find(u-n)]; v[x][y] = v[y][x] = true;
        }
    }
    if (t == 1) return 0;
    memset(d, e[0] = f[0] = 0, sizeof(d));
    for (int i=0; i<t; ++i) for (int j=0; j<t; ++j) if (v[i][j]) s[i][d[i]++] = j;
    for (int i=1; i<t; ++i) {
        if (v[i][0]) g[0][e[0]++] = i;
        r[0][f[0]++] = i;
    }
    for (int i=1; i<t; ++i) if (IDAStar(0, i)) return i;
    return t;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) cout << solve() << endl;
    return 0;
}