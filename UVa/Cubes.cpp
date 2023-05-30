/**
 * UVa10601
 * 立方体
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 12
int rot[][N] = {
    {3, 0, 1, 2, 7, 4, 5, 6, 11, 8, 9, 10},
    {2, 9, 6, 10, 0, 8, 4, 11, 1, 5, 7, 3},
    {11, 3, 10, 7, 8, 1, 9, 5, 0, 2, 6, 4}
}, r[64][N], c[N], f = 0;

bool find(int i) {
    for (int k=0; k<N; ++k) if (r[i][k] != r[f][k]) return false;
    return true;
}

void gen_r() {
    for (int i=0; i<64; ++i) {
        int k[] = {i&3, i>>2&3, i>>4}, (&v)[N] = r[f], cc = 0;
        int p[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
        for (int j=0; j<N; ++j) v[j] = p[j];
        for (int j=0; j<3; ++j) for (int c=0; c<k[j]; ++c) {
            for (int t=0; t<N; ++t) v[t] = p[rot[j][t]];
            for (int t=0; t<N; ++t) p[t] = v[t];
        }
        for (int j=0; j<f; ++j) if (find(j)) ++cc;
        if (!cc) ++f;
    }
}

bool is_fixed_point(int (&r)[N]) {
    for (int i=0; i<N; ++i) if (c[r[i]] != c[i]) return false;
    return true;
}

void solve() {
    for (int i=0; i<N; ++i) cin >> c[i];
    sort(c, c+N);
    int s = 0;
    do {
        for (int i=0; i<f; ++i) if (is_fixed_point(r[i])) ++s;
    } while (next_permutation(c, c+N));
    cout << s / f << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    gen_r();
    int t; cin >> t;
    while (t--) solve();
    return 0;
}