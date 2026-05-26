/**
 * UVa1497/LA5719
 * 给程序员的一封信
 * Beijing 2011
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int n, t; const double e = M_PI/180.; char s[10]; double a[4][4], p[4][4], c[4][4], r[52][4][4];

void identity_mat(double (&t)[4][4]) {
    for (int i=0; i<4; ++i) for (int j=0; j<4; ++j) t[i][j] = i==j ? 1. : 0.;
}

void trans_mat(double tx, double ty, double tz, double (&t)[4][4]) {
    identity_mat(t); t[0][3] = tx; t[1][3] = ty; t[2][3] = tz;
}

void scale_mat(double a, double b, double c, double (&t)[4][4]) {
    identity_mat(t); t[0][0] = a; t[1][1] = b; t[2][2] = c;
}

void rot_mat(double a, double b, double c, double d, double (&t)[4][4]) {
    double s = sqrt(a*a + b*b + c*c); a /= s; b /= s; c /= s; d *= e;
    double co = cos(d), si = sin(d), c1 = 1.-co; identity_mat(t);
    t[0][0] = co + a*a*c1; t[0][1] = a*b*c1 - c*si; t[0][2] = a*c*c1 + b*si;
    t[1][0] = a*b*c1 + c*si; t[1][1] = co + b*b*c1; t[1][2] = b*c*c1 - a*si;
    t[2][0] = a*c*c1 - b*si; t[2][1] = b*c*c1 + a*si; t[2][2] = co + c*c*c1;
}

void copy(const double (&a)[4][4], double (&b)[4][4]) {
    for (int i=0; i<4; ++i) for (int j=0; j<4; ++j) b[i][j] = a[i][j];
}

void mat_mul(const double (&a)[4][4], const double (&b)[4][4], double (&c)[4][4]) {
    for (int i=0; i<4; ++i) for (int j=0; j<4; ++j) {
        c[i][j] = 0.;
        for (int k=0; k<4; ++k) c[i][j] += a[i][k]*b[k][j];
    }
}

void mat_pow(const double (&x)[4][4], int y, double (&b)[4][4]) {
    identity_mat(b); copy(x, p);
    while (y) {
        if (y & 1) mat_mul(b, p, a), copy(a, b);
        if (y >>= 1) mat_mul(p, p, a), copy(a, p);
    }
}

void dfs(int k = -1) {
    while (true) {
        cin >> s;
        if (s[0] == 'r' && s[1] == 'e') {
            int k1; cin >> k1; identity_mat(r[++t]); dfs(k1);
        } else if (s[0] == 'e') {
            if (k >= 0) mat_pow(r[t], k, c), mat_mul(c, r[--t], a), copy(a, r[t]);
            return;
        } else {
            if (s[0] == 't') {
                double x, y, z; cin >> x >> y >> z; trans_mat(x, y, z, c);
            } else if (s[0] == 's') {
                double x, y, z; cin >> x >> y >> z; scale_mat(x, y, z, c);
            } else {
                double x, y, z, d; cin >> x >> y >> z >> d; rot_mat(x, y, z, d, c);
            }
            mat_mul(c, r[t], a); copy(a, r[t]);
        }
    }
}

void solve() {
    identity_mat(r[t=0]); dfs();
    while (n--) {
        double x, y, z; cin >> x >> y >> z;
        cout << r[0][0][0]*x + r[0][0][1]*y + r[0][0][2]*z + r[0][0][3] + 1e-6 << ' ' << 
            r[0][1][0]*x + r[0][1][1]*y + r[0][1][2]*z + r[0][1][3] + 1e-6 << ' ' << 
            r[0][2][0]*x + r[0][2][1]*y + r[0][2][2]*z + r[0][2][3] + 1e-6 << endl;
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(2);
    while (cin >> n && n) solve();
    return 0;
}