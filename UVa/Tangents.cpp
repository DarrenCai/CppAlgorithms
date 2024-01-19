/**
 * UVa10674
 * 切线
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

int xs, ys, rs, x2, y2, r2;
struct node {
    double sx, sy, tx, ty, l;
    bool operator< (const node& rhs) const {
        return sx != rhs.sx ? sx < rhs.sx : sy < rhs.sy; 
    }
    void print() {
        cout << sx << ' ' << sy << ' ' << tx << ' ' << ty << ' ' << l << endl;
    }
} ans[4];

void solve() {
    if (xs==x2 && ys==y2 && rs==r2) {
        cout << -1 << endl;
        return;
    }
    double l = sqrt((xs-x2)*(xs-x2) + (ys-y2)*(ys-y2));
    if (l+min(rs,r2) < max(rs, r2)) {
        cout << 0 << endl;
        return;
    }
    if (l+min(rs,r2) == max(rs, r2)) {
        cout << 1 << endl;
        if (rs < r2) {
            double a = atan2(ys-y2, xs-x2), x = xs + rs*cos(a), y = ys + rs*sin(a);
            cout << x << ' ' << y << ' ' << x << ' ' << y << " 0" << endl;
        } else {
            double a = atan2(y2-ys, x2-xs), x = x2 + r2*cos(a), y = y2 + r2*sin(a);
            cout << x << ' ' << y << ' ' << x << ' ' << y << " 0" << endl;
        }
        return;
    }
    double a = atan2(y2-ys, x2-xs), b = acos((rs-r2)/l);
    ans[0].sx = xs + rs*cos(a+b); ans[0].sy = ys + rs*sin(a+b);
    ans[0].tx = x2 + r2*cos(a+b); ans[0].ty = y2 + r2*sin(a+b); ans[0].l = l*sin(b);
    ans[1].sx = xs + rs*cos(a-b); ans[1].sy = ys + rs*sin(a-b);
    ans[1].tx = x2 + r2*cos(a-b); ans[1].ty = y2 + r2*sin(a-b); ans[1].l = l*sin(b);
    if (l < rs+r2) {
        cout << 2 << endl;
        sort(ans, ans+2); ans[0].print(); ans[1].print();
    } else if (l > rs+r2) {
        cout << 4 << endl;
        b = acos((rs+r2)/l);
        ans[2].sx = xs + rs*cos(a+b); ans[2].sy = ys + rs*sin(a+b);
        ans[2].tx = x2 - r2*cos(a+b); ans[2].ty = y2 - r2*sin(a+b); ans[2].l = l*sin(b);
        ans[3].sx = xs + rs*cos(a-b); ans[3].sy = ys + rs*sin(a-b);
        ans[3].tx = x2 - r2*cos(a-b); ans[3].ty = y2 - r2*sin(a-b); ans[3].l = l*sin(b);
        sort(ans, ans+4); ans[0].print(); ans[1].print(); ans[2].print(); ans[3].print();
    } else {
        cout << 3 << endl;
        ans[2].sx = ans[2].tx = xs + rs*cos(a); ans[2].sy = ans[2].ty = ys + rs*sin(a); ans[2].l = 0.;
        sort(ans, ans+3); ans[0].print(); ans[1].print(); ans[2].print();
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(5);
    while (cin >> xs >> ys >> rs >> x2 >> y2 >> r2 && rs) solve();
    return 0;
}