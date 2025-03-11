/**
 * UVa12303
 * 组合变换
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define N 50010
double pl[N][4], p[N][3], l[3][4], r[4][4], v[3][4], e = M_PI/180;

double mul(const double (&r)[4], const double *v3) {
    return r[0]*v3[0] + r[1]*v3[1] + r[2]*v3[2] +  + r[3];
}

void load_trans(double a, double b, double c) {
    l[0][0] = 1.; l[0][1] = 0.; l[0][2] = 0.; l[0][3] = a;
    l[1][0] = 0.; l[1][1] = 1.; l[1][2] = 0.; l[1][3] = b;
    l[2][0] = 0.; l[2][1] = 0.; l[2][2] = 1.; l[2][3] = c;
}

void load_rot(double a, double b, double c, double theta) {
    double si = sin(theta), co = cos(theta), s = sqrt(a*a+b*b+c*c); a /= s; b /= s; c /= s;
    l[0][0] = co+a*a*(1-co); l[0][1] = a*b*(1-co)-c*si; l[0][2] = a*c*(1-co)+b*si; l[0][3] = 0.;
    l[1][0] = a*b*(1-co)+c*si; l[1][1] = co+b*b*(1-co); l[1][2] = b*c*(1-co)-a*si; l[1][3] = 0.;
    l[2][0] = a*c*(1-co)-b*si; l[2][1] = b*c*(1-co)+a*si; l[2][2] = co+c*c*(1-co); l[2][3] = 0.;
}

void load_scale(double a, double b, double c) {
    l[0][0] = a; l[0][1] = 0.; l[0][2] = 0.; l[0][3] = 0.;
    l[1][0] = 0.; l[1][1] = b; l[1][2] = 0.; l[1][3] = 0.;
    l[2][0] = 0.; l[2][1] = 0.; l[2][2] = c; l[2][3] = 0.;
}

void trans_plane(double a, double b, double c, double d) {
    double x = max(max(abs(a), abs(b)), abs(c));
    if (abs(a) == x) {
        v[0][0] = -d/a; v[0][1] = 0.; v[0][2] = .0;
        v[1][0] = -(c+d)/a; v[1][1] = 0.; v[1][2] = 1.;
        v[2][0] = -(b+d)/a; v[2][1] = 1.; v[2][2] = 0.;
    } else if (abs(b) == x) {
        v[0][0] = 0.; v[0][1] = -d/b;  v[0][2] = 0.;
        v[1][0] = 0.; v[1][1] = -(c+d)/b; v[1][2] = 1.;
        v[2][0] = 1.; v[2][1] = -(a+d)/b; v[2][2] = 0.;
    } else {
        v[0][0] = 0.; v[0][1] = 0.; v[0][2] = -d/c;
        v[1][0] = 0.; v[1][1] = 1.; v[1][2] = -(b+d)/c;
        v[2][0] = 1.; v[2][1] = 0.; v[2][2] = -(a+d)/c;
    }
    for (int i=0; i<3; ++i)
        l[i][0] = mul(r[0], v[i]), l[i][1] = mul(r[1], v[i]), l[i][2] = mul(r[2], v[i]);
    double x1 = l[1][0]-l[0][0], y1 = l[1][1]-l[0][1], z1 = l[1][2]-l[0][2],
        x2 = l[2][0]-l[0][0], y2 = l[2][1]-l[0][1], z2 = l[2][2]-l[0][2],
        e = y1*z2 - z1*y2, f = x2*z1 - x1*z2, g = x1*y2 - x2*y1, s = sqrt(e*e + f*f + g*g);
        e /= s; f /= s; g /= s;
    cout << e << ' ' << f << ' ' << g << ' ' << -(e*l[0][0] + f*l[0][1] + g*l[0][2]) << endl;
}

void solve() {
    int m, n, t; char s[10]; double a, b, c, d; cin >> n >> m >> t;
    for (int i=0; i<n; ++i) cin >> p[i][0] >> p[i][1] >> p[i][2];
    for (int i=0; i<m; ++i) cin >> pl[i][0] >> pl[i][1] >> pl[i][2] >> pl[i][3];
    for (int i=0; i<4; ++i) for (int j=0; j<4; ++j) r[i][j] = i==j ? 1. : 0.;
    while (t--) {
        cin >> s >> a >> b >> c;
        if (s[0] == 'T') load_trans(a, b, c);
        else if (s[0] == 'R') cin >> d, load_rot(a, b, c, d*e);
        else load_scale(a, b, c);
        for (int i=0; i<3; ++i) for (int j=0; j<4; ++j)
            v[i][j] = l[i][0]*r[0][j] + l[i][1]*r[1][j] + l[i][2]*r[2][j] + l[i][3]*r[3][j];
        for (int i=0; i<3; ++i) for (int j=0; j<4; ++j) r[i][j] = v[i][j];
    }
    for (int i=0; i<n; ++i) cout << mul(r[0], p[i]) << ' ' << mul(r[1], p[i]) << ' ' << mul(r[2], p[i]) << endl;
    for (int i=0; i<m; ++i) trans_plane(pl[i][0], pl[i][1], pl[i][2], pl[i][3]);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(2);
    solve();
    return 0;
}