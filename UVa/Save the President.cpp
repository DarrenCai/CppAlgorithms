/**
 * UVa11589
 */

#include <iostream>
#include <cstring>
using namespace std;

#define FOR(i, l, r) for(int i=l; i<=r; ++i)
#define exp(i, b0, b1, b2, b3) int j=i, b0=j&1, b1=(j>>=1)&1, b2=(j>>=1)&1, b3=(j>>=1)&1
#define coeff(b0, b1, b2, b3) ((b0+b1+b2+b3)&1 ? 1 : -1)
int s[20][20][20][100], kase = 0, dx, dy, dz, n, q; char c1[6], c2[6];

void solve() {
    memset(s, 0, sizeof(s));
    for (int i=0; i<n; ++i) {
        int x1, y1, z1, x2, y2, z2, t1, t2;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> c1 >> c2;
        t1 = 4*(10*(c1[0]-'0') + c1[1]-'0') + (10*(c1[3]-'0') + c1[4]-'0') / 15;
        t2 = 4*(10*(c2[0]-'0') + c2[1]-'0') + (10*(c2[3]-'0') + c2[4]-'0') / 15;
        FOR(x, x1+1, x2) FOR(y, y1+1, y2) FOR(z, z1+1, z2) FOR(t, t1+1, t2) s[x][y][z][t] = 1;
    }
    FOR(x, 1, dx) FOR(y, 1, dy) FOR(z, 1, dz) FOR(t, 1, 96) FOR(i, 1, 15) {
        exp(i, b0, b1, b2, b3);
        s[x][y][z][t] += coeff(b0, b1, b2, b3)*s[x-b0][y-b1][z-b2][t-b3];
    }
    cout << "3D World " << ++kase << ':' << endl;
    while (q--) {
        int x1, y1, z1, t1, ans = 0;
        cin >> x1 >> y1 >> z1 >> c1;
        t1 = 4*(10*(c1[0]-'0') + c1[1]-'0') + (10*(c1[3]-'0') + c1[4]-'0') / 15;
        FOR(x, x1, dx) FOR(y, y1, dy) FOR(z, z1, dz) FOR(t, t1, 96) {
            int c = s[x][y][z][t];
            FOR(i, 1, 15) {
                exp(i, b0, b1, b2, b3);
                c -= coeff(b0, b1, b2, b3)*s[x-x1*b0][y-y1*b1][z-z1*b2][t-t1*b3];
            }
            if (!c) ++ans;
        }
        ans ? cout << ans << " safe place(s) found" << endl : cout << "No safe place(s) found" << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> dx >> dy >> dz >> q && n) solve();
    return 0;
}