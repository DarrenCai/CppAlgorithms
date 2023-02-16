/**
 * UVa11768
 * 格点判定
 */

#include <iostream>
using namespace std;

int read() {
    int x, r; char _;
    cin >> x >> _ >> r;
    return 10*x + r;
}

int gcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1; y = 0; return a;
    } else {
        int g = gcd(b, a%b, y, x);
        y -= a/b*x;
        return g;
    }
}

int solve() {
    int x1 = read(), y1 = read(), x2 = read(), y2 = read(), dx = x2-x1, dy = y2-y1, x, y;
    if (dx == 0) {
        dx = dy; dy = 0; x = x1; x1 = y1; y1 = x; y = y2; y2 = x2; x2 = y;
    }
    if (dx == 0) return x1%10 || y1%10 ? 0 : 1;
    int g = gcd(dx, dy, x, y);
    dx /= g; dy /= g;
    int g1 = gcd(dx, 10, x, y);
    if (x1 % g1) return 0;
    long long c1 = -x1%10/g1*(long long)x;
    int g2 = gcd(dy, 10, x, y);
    if (y1%g2) return 0;
    long long c = -y1%10/g2*(long long)x - c1;
    g1 = 10/g1; g2 = 10/g2;
    g = gcd(g1, g2, x, y);
    if (c % g) return 0;
    c = x1 + dx * (c1 + c/g * g1*x); g = abs(g2/g * dx*g1);
    long long a = min(x1, x2) - c, b = max(x1, x2) - c;
    return b / g - (b%g < 0) - a / g + (a%g <= 0);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}