/**
 * UVa1403/LA3962
 * CERC 2007
 * 注意：分段函数使用辛普森公式求积分时需要分段处理
 */

#include <iostream>
#include <iomanip>
#include <stack>
using namespace std;

#define err 6e-5
#define PI 3.14159265358979323846

struct op {
    double v; int f;
    op(int f=0, double v=0.): v(v), f(f) {}
};
stack<op> s, r, t; double h, b, y, (*f)(double);

void build(stack<op>& e, bool r = false, bool p = false) {
    char c; cin >> c;
    if (c == 'x') {
        s.push(op(1));
    } else if (c >= '0' && c <= '9') {
        cin.unget();
        double v; cin >> v;
        s.push(op(0, v));
    } else if (c == '(') {
        while (cin.peek() != ')') build(e, true);
        cin.get();
        if (!r && cin.peek() != '\n') return build(e, false, true);
    } else if (c == '*' || c == '/') {
        int f = s.top().f;
        if (!p && (f == '+' || f == '-')) {
            s.pop();
            build(e, true);
            s.push(op(c));
            s.push(op(f));
        } else {
            build(e, true);
            s.push(op(c));
        }
    } else {
        if (s.empty()) s.push(op());
        build(e, true);
        s.push(op(c));
    }
    if (r) return;
    if (cin.peek() == '\n') {
        while (!s.empty()) e.push(s.top()), s.pop();
        return;
    }
    build(e);
}

double eval(const stack<op>& e, double x) {
    stack<op> s(e); stack<double> t;
    while (!s.empty()) {
        int f = s.top().f;
        if (f > 1) {
            double r = t.top(); t.pop();
            double l = t.top(); t.pop();
            t.push(f=='+' ? l+r : (f=='-' ? l-r : (f=='*' ? l*r : l/r)));
        } else t.push(f ? x : s.top().v);
        s.pop();
    }
    return t.top();
}

double f1(double x) {
    double c = eval(r, x);
    if (x <= b) return 2.5*c*c*x;
    double d = c-eval(t, x);
    return (2.5*c*c - (x>y ? 2.5 : 1.5)*d*d)*x;
}

double f2(double x) {
    double c = eval(r, x);
    if (x <= b) return 2.5*c*c;
    double d = c-eval(t, x);
    return 2.5*c*c - (x>y ? 2.5 : 1.5)*d*d;
}

double f3(double x) {
    double y = eval(r, x) - eval(t, x);
    return y*y;
}

double simpson(double a, double b) {
    double c = (a+b)/2;
    return (f(a) + 4*f(c) + f(b))*(b-a)/6;
}

double asr(double l, double r, double s, double eps) {
    double m = (l+r)/2, s1 = simpson(l, m), s2 = simpson(m, r), e = (s1+s2-s)/15.;
    if (abs(e) < eps) return s1+s2+e;
    return asr(l, m, s1, eps/2) + asr(m, r, s2, eps/2);
}

void solve() {
    while (!r.empty()) r.pop();
    while (!t.empty()) t.pop();
    build(r); build(t); f = f1; y = b;
    double s = asr(0, b, simpson(0, b), err) + asr(b, h, simpson(b, h), err);
    f = f2; s /= asr(0, b, simpson(0, b), err) + asr(b, h, simpson(b, h), err);
    if (s <= b) {
        cout << "Pour 0.000 litres / 0.000 cm of water." << endl;
        return;
    }
    double l = b, r = s, x;
    while (r-l > err) {
        f = f1; x = y = (2*l+r)/3;
        double s1 = asr(0, b, simpson(0, b), err) + asr(b, y, simpson(b, y), err) + asr(y, h, simpson(y, h), err);
        f = f2; s1 /= asr(0, b, simpson(0, b), err) + asr(b, y, simpson(b, y), err) + asr(y, h, simpson(y, h), err);
        f = f1; y = (l+2*r)/3;
        double s2 = asr(0, b, simpson(0, b), err) + asr(b, y, simpson(b, y), err) + asr(y, h, simpson(y, h), err);
        f = f2; s2 /= asr(0, b, simpson(0, b), err) + asr(b, y, simpson(b, y), err) + asr(y, h, simpson(y, h), err);
        s1 > s2 ? l = x : r = y;
    }
    f = f3;
    cout << "Pour " << PI*asr(b, r, simpson(b, r), err)/1000 << " litres / " << r-b << " cm of water." << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(3);
    while (cin>>h>>b && h) solve();
    return 0;
}