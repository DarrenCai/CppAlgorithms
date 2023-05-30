/**
 * UVa10601
 * 立方体
 */

#include <iostream>
using namespace std;

int t[7], c[13][13];

int no_rot() {
    int s = 1;
    for (int i=1, p=12; i<7; ++i) s *= c[p][t[i]], p -= t[i];
    return s;
}

int diag_points_rot() {
    int s = 8, cc = 4;
    for (int i=1; i<7; ++i) {
        if (t[i] % 3) return 0;
        s *= c[cc][t[i]/3]; cc -= t[i]/3;
    }
    return s;
}

int diag_edges_rot() {
    int cc = 0, s = 1;
    for (int i=1; i<7; ++i) if (t[i] & 1)  if (++cc > 2) return 0;
    if (cc == 1) return 0;
    cc == 2 ? (cc = 5, s = 2) : cc = 6;
    for (int i=1; i<7; ++i) s *= c[cc][t[i]>>1], cc -= t[i]>>1;
    return 6*s;
}

int opp_faces_rot_90() {
    int cc = 0;
    for (int i=1; i<7; ++i) {
        if (t[i] % 4) return 0;
        cc += min(t[i]>>2, 1);
    }
    return cc==3 ? 6 : (cc==2 ? 3 : 1);
}

int opp_faces_rot_180() {
    int s = 1, cc = 6;
    for (int i=1; i<7; ++i) {
        if (t[i] & 1) return 0;
        s *= c[cc][t[i]>>1]; cc -= t[i]>>1;
    }
    return s;
}

int opp_faces_rot() {
    return 6*opp_faces_rot_90() + 3*opp_faces_rot_180();
}

void solve() {
    for (int i=1; i<7; ++i) t[i] = 0;
    for (int i=0; i<12; ++i) {
        int x; cin >> x;
        ++ t[x];
    }
    cout << (no_rot() + diag_points_rot() + diag_edges_rot() + opp_faces_rot()) / 24 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    c[0][0] = 1;
    for (int i=1; i<13; ++i) {
        c[i][0] = 1;
        for (int j=1; j<=i; ++j) c[i][j] = c[i-1][j-1] + c[i-1][j];
    }
    int t; cin >> t;
    while (t--) solve();
    return 0;
}