/**
 * UVa10733
 */

#include <iostream>
using namespace std;

long long c;

long long no_rot() {
    return c*c*c*c*c*c;
}

long long diag_points_rot() {
    return 8*c*c;
}

long long diag_edges_rot() {
    return 6*c*c*c;
}

long long opp_faces_rot_90() {
    return 6*c*c*c;
}

long long opp_faces_rot_180() {
    return 3*c*c*c*c;
}

long long opp_faces_rot() {
    return opp_faces_rot_90() + opp_faces_rot_180();
}

void solve() {
    cout << (no_rot() + diag_points_rot() + diag_edges_rot() + opp_faces_rot()) / 24 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>c && c) solve();
    return 0;
}
