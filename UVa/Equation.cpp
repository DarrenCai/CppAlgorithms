/**
 * UVa1661
 * 方程
 */

#include <iostream>
using namespace std;

#define N 81
char s[81]; short x;

struct node {
    long long p, q;
    node():p(0),q(1) {}
    void operator += (const node& rhs) {
        p = p*rhs.q + rhs.p*q;
        q *= rhs.q;
    }
    void operator -= (const node& rhs) {
        p = p*rhs.q - rhs.p*q;
        q *= rhs.q;
    }
    void operator *= (const node& rhs) {
        p *= rhs.p;
        q *= rhs.q;
    }
    void operator /= (const node& rhs) {
        p *= rhs.q;
        q *= rhs.p;
    }
};

short l(short b) {
    if (s[b] >= '0') {
        if (s[--b] >= '0') return b;
        return l(b-1);
    }
    short r = l(b-1) - 1;
    return s[r] >= '0' ? r : l(r-1);
}

short r(short b) {
    if (s[b] >= '0') return b;
    return l(b-1);
}

long long gcd(long long a, long long b) {
    if (a > b) return gcd(b, a);
    if (a < 0) return gcd(-a, b);
    if (a==0) return b;
    if (a & 1) {
        if (b & 1) return gcd(a, (b-a)>>1);
        return gcd(a, b>>1);
    } else {
        if (b & 1) return gcd(a>>1, b);
        return gcd(a>>1, b>>1)<<1;
    } 
}

node calc(short a, short b) {
    if (a == b) {
        node v; v.p = s[a] - '0';
        return v;
    }
    node lhs, rhs;
    if (a+2 == b) {
        lhs.p = s[a] - '0'; rhs.p = s[b-1] - '0';
    } else if (s[b-1] >= '0') {
        rhs.p = s[b-1] - '0';
        lhs = calc(a, b-2);
    } else {
        short i = l(b-2);
        rhs = calc(i, b-1);
        lhs = calc(a, i-1);
    }
    s[b]=='*' ? lhs*=rhs : (s[b]=='/' ? lhs/=rhs : (s[b]=='+' ? lhs+=rhs : lhs-=rhs));
    return lhs;
}

void solve(short a, short b, node c = node()) {
    if (a == b) {
        if (s[a] < 'X') {
            cout << (c.p == (s[a]-'0')*c.q ? "MULTIPLE" : "NONE") << endl;
        } else {
            long long g = gcd(c.p, c.q);
            if (c.q < 0) g *= -1;
            cout << "X = " << c.p/g << '/' << c.q/g << endl;
        }
        return;
    }
    if (x<a || x>b) {
        node v = calc(a, b);
        cout << (c.p*v.q == v.p*c.q ? "MULTIPLE" : "NONE") << endl;
        return;
    }
    short l = r(b-1); node v = x<l ? calc(l, b-1) : calc(a, l-1);
    if (v.p==0 && (s[b]=='*' || s[b]=='/')) {
        cout << (c.p == 0 ? "MULTIPLE" : "NONE") << endl;
    } else {
        if (s[b] == '/') {
            if (x < l) {
                c *= v; solve(a, l-1, c);
            } else if (c.p == 0) {
                cout << "NONE" << endl;
            } else {
                v /= c; solve(l, b-1, v);
            }
        } else {
            if (s[b]=='-' && x>=l) {
                v -= c; solve(l, b-1, v);
            } else {
                s[b]=='*' ? c /= v : (s[b]=='+' ? c -= v : c += v);
                x<l ? solve(a, l-1, c) : solve(l, b-1, c);
            }
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin.getline(s, N)) {
        short n = -1; x = -1;
        for (short i=0; s[i]; ++i) if (s[i] != ' ') {
            s[++n] = s[i];
            if (s[i] == 'X') x = n;
        }
        solve(0, n, node());
    }
}