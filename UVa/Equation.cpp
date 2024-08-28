/**
 * UVa1661/LA4047
 * 方程
 * NEERC 2007
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 32
struct frac {
    long long p, q;
    void calc(char op, const frac& x) {
        if (op == '+') p = p*x.q + x.p*q, q *= x.q;
        else if (op == '-') p = p*x.q - x.p*q, q *= x.q;
        else if (op == '*') q *= x.q, p *= x.p;
        else q *= x.p, p *= x.q;
    }
    void print() const {
        long long g = abs(__gcd(p, q));
        if (q < 0) g = -g;
        cout << "X = " << p/g << '/' << q/g << endl;
    }
};
int s[N], l[N], r[N], n; char op[N];

bool has_x(int i) {
    if (op[i] == 'X') return true;
    if (op[i] < '0') return has_x(l[i]) || has_x(r[i]);
    return false;
}

frac calc(int i) {
    if (op[i] >='0' && op[i] <= '9') return {op[i]-'0', 1};
    frac x = calc(l[i]); x.calc(op[i], calc(r[i]));
    return x;
}

void solve(int i, frac& c) {
    if (i < 0) return;
    if (op[i] == 'X') return c.print();
    if (op[i] >= '0') cout << (c.p != (op[i]-'0') * c.q ? "NONE" : "MULTIPLE") << endl;
    else if (has_x(l[i])) {
        frac f = calc(r[i]);
        if (f.p == 0 && (op[i] == '*' || op[i] == '/')) cout << (c.p ? "NONE" : "MULTIPLE") << endl;
        else c.calc(op[i] == '*' ? '/' : (op[i] == '/' ? '*' : (op[i] == '+' ? '-' : '+')), f), solve(l[i], c);
    } else if (has_x(r[i])) {
        frac f = calc(l[i]);
        if (f.p == 0 && (op[i] == '*' || op[i] == '/')) cout << (c.p ? "NONE" : "MULTIPLE") << endl;
        else if (op[i] == '/' && c.p == 0) cout << "NONE" << endl;
        else if (op[i] == '-' || op[i] == '/') f.calc(op[i], c), solve(r[i], f);
        else c.calc(op[i] == '*' ? '/' : '-', f), solve(r[i], c);
    } else {
        frac f = calc(i); cout << (f.p * c.q != c.p * f.q ? "NONE" : "MULTIPLE") << endl;
    }
}

void solve() {
    int t = n = 0, k; frac c{0, 1};
    if (cin.peek() == '\n') cin.get();
    while ((k = cin.peek()) != '\n' && k != EOF) if (k != ' ') {
        cin >> op[n++];
        if (k >= '0') s[t++] = n-1;
        else r[n-1] = s[--t], l[n-1] = s[t-1], s[t-1] = n-1;
    } else cin.get();
    solve(n-1, c);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin.peek() != EOF) solve();
    return 0;
}