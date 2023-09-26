/**
 * UVa12413
 * 高精度十进制小数计算器
 */

#include <iostream>
using namespace std;

#define N 82
char func[8]; short s[N], t[N], p;
bool ge(const short *a, const short *b, short m, short n) {
    for (short i=0, j = max(m, n); i<j; ++i) {
        short x = i<m ? a[i] : 0, y = i<n ? b[i] : 0;
        if (x != y) return x > y;
    }
    return true;
}
bool not_zero(const short (&a)[N], short n) {
    for (int i=0; i<n; ++i) if (a[i]) return true;
    return false;
}
struct decimal {
    short v[N], n, p, neg;
    decimal():v{0}, n(1), p(0), neg(0) {}
    void trim() {
        while (n && n-1>p && !v[n-1]) --n;
        while (n && v[0] == 0) {
            for (int i=1; i<n; ++i) v[i-1] = v[i];
            --n; --p;
        }
        if (n == 0) v[0] = 0, n = 1, p = 0;
    }
    void read() {
        char c; cin >> c;
        neg = c == '-'; n = 0; p = -1;
        if (c>='0' && c<='9') cin.unget();
        while ((c = cin.get()) != ' ') c == '.' ? p = n-1 : v[n++] = c - '0';
        if (p < 0) p = n-1;
        trim();
    }
    void write(short s);
    bool abs_ge(decimal& rhs) const {
        if (is_zero()) return rhs.is_zero();
        if (rhs.is_zero()) return true;
        if (p != rhs.p) return p > rhs.p;
        for (short i=0, m=max(n, rhs.n); i<m; ++i) {
            int x = i<n ? v[i] : 0, y = i<rhs.n ? rhs.v[i] : 0;
            if (x != y) return x > y;
        }
        return true;
    }
    bool is_zero() const {
        return (n==1 && v[0]==0) || -p > N;
    }
    void add(decimal& x) {
        bool ge = abs_ge(x); short g = p - x.p;
        if (ge) {
            for (int i=0; i<n; ++i) s[i] = v[i];
            for (int i=0; i<x.n; ++i) t[i] = x.v[i];
        } else {
            g = x.p - p; p = x.p;
            for (int i=0; i<x.n; ++i) s[i] = x.v[i];
            for (int i=0; i<n; ++i) t[i] = v[i];
        }
        short f = neg ^ x.neg, a = ge ? n : x.n, b = ge ? x.n : n, r = 0;
        n = min(max(int(a), g+b), N); neg = ge ? neg : x.neg;
        for (int i=n-1; i>=0; --i) {
            short va = i<a ? s[i] : 0, vb = i<g ? 0 : (i-g<b ? t[i-g] : 0);
            v[i] = r + (f ? va - vb : va + vb);
            r = v[i] > 9 ? (v[i] -= 10, 1) : (v[i] < 0 ? (v[i] += 10, -1) : 0);
        }
        if (r) {
            ++p;
            n = min(n+1, N);
            for (int i=n-1; i>0; --i) v[i] = v[i-1];
            v[0] = 1;
        }
        trim();
    }
    void div(unsigned int x) {
        if (is_zero()) return;
        int r = v[0], i = 0, m = n;
        for (int j=1; j<m; ++j) s[j] = v[j];
        while (r < x) --p, r = 10*r + (++i<m ? s[i] : 0);
        for (n=0; (r || i<m) && n<N; ++n) v[n] = r/x, r = 10*(r%x) + (++i<m ? s[i] : 0);
    }
    void _div_x(short d, short x) {
        short r = d; p=0; neg = 0;
        while (r < x) --p, r *= 10;
        for (n=0; r && n<N; ++n) v[n] = r/x, r = 10*(r%x);
    }
    void add(decimal& x, decimal& y);
    void sub(decimal& x, decimal& y);
    void mul(decimal& x, decimal& y);
    void div(decimal& x, decimal& y);
    void ln(decimal& x);
    void exp(decimal& x);
    void pow(decimal& x, decimal& y);
    void atan(decimal& x);
    void atan2(decimal& y, decimal& x);
    void sqrt(decimal& x);
    void asin(decimal& x);
    void acos(decimal& x);
    void sin(decimal& x);
    void cos(decimal& x);
    void tan(decimal& x);
} r, x, y, z, w, u, q, c, ln2, pi_2;

void decimal::write(short s) {
    x.v[0] = 5; x.n = 1; x.p = -s-1; x.neg = neg; add(x);
    if ((func[0]=='m' || func[0]=='d') && is_zero()) neg = 0;
    if (neg) cout << '-';
    cout << (p>=0 ? v[0] : 0);
    for (int i=1; i<=p; ++i) cout << (i<n ? v[i] : 0);
    if (s) {
        cout << '.';
        int i = p+1;
        while (i<0 && s) ++i, --s, cout << 0;
        while (i<n && s) --s, cout << v[i++];
        while (s) --s, cout << 0;
    }
    cout << endl;
}

void decimal::add(decimal& x, decimal& y) {
    bool ge = x.abs_ge(y);
    const decimal &a = ge ? x : y, &b = ge ? y : x;
    short f = a.neg ^ b.neg, g = a.p - b.p, r = 0;
    n = min(max(int(a.n), g+b.n), N); p = a.p; neg = a.neg;
    for (int i=n-1; i>=0; --i) {
        short va = i<a.n ? a.v[i] : 0, vb = i<g ? 0 : (i-g<b.n ? b.v[i-g] : 0);
        v[i] = r + (f ? va - vb : va + vb);
        r = v[i] > 9 ? (v[i] -= 10, 1) : (v[i] < 0 ? (v[i] += 10, -1) : 0);
    }
    if (r) {
        ++p;
        n = min(n+1, N);
        for (int i=n-1; i>0; --i) v[i] = v[i-1];
        v[0] = 1;
    }
    trim();
}
void decimal::sub(decimal& x, decimal& y) {
    y.neg ^= 1;
    add(x, y);
    y.neg ^= 1;
}
void decimal::mul(decimal& x, decimal& y) {
    if (x.is_zero() || y.is_zero()) {
        n=1; v[0] = 0; p = 0; neg = 0;
        return;
    }
    neg = x.neg ^ y.neg; p = x.p + y.p; n = x.n;
    for (int i=0; i<n; ++i) v[i] = 0;
    short r = 0;
    for (int i=y.n-1; i>=0; --i) {
        n = min(n+1, N);
        for (int j=n-1; j>0; --j) v[j] = v[j-1];
        v[0] = r; r = 0;
        for (int j=x.n-1; j>=0; --j) (v[j] += x.v[j]*y.v[i] + r) > 9 ? (r = v[j]/10, v[j]%=10) : r = 0;
    }
    if (r) {
        n = min(n+1, N);
        for (int j=n-1; j>0; --j) v[j] = v[j-1];
        v[0] = r;
        ++p;
    }
    trim();
}
void decimal::div(decimal& x, decimal& y) {
    if (x.is_zero()) {
        n=1; v[0] = 0; p = 0; neg = 0;
        return;
    }
    neg = x.neg ^ y.neg; p = x.p - y.p; n = 0;
    short m = x.n; for (int i=0; i<m; ++i) s[i] = x.v[i];
    bool f = !ge(s, y.v, m, y.n);
    if (f) --p;
    while (n<N && not_zero(s, m)) {
        short z = min((f ? (10*s[0] + (m>1 ? s[1] : 0)) : s[0]) / y.v[0], 9), r = 0;
        for (int i=y.n-1; i>=0; --i) (t[i] = z*y.v[i] + r) > 9 ? (r = t[i]/10, t[i] %= 10) : r = 0;
        while ((f && (r>s[0] || (r==s[0] && !ge(s+1, t, m-1, y.n)))) || (!f && (r || !ge(s, t, m, y.n)))) {
            --z; r = 0;
            for (int i=y.n-1; i>=0; --i) (t[i] = z*y.v[i] + r) > 9 ? (r = t[i]/10, t[i] %= 10) : r = 0;
        }
        v[n++] = z; r = 0;
        if (f) {
            --m; for (int i=0; i<m; ++i) s[i] = s[i+1];
        }
        for (int i=max(m, y.n)-1; i>=0; --i)
            r = (s[i] = (i<m ? s[i] : 0) - r - (i<y.n ? t[i] : 0)) < 0 ? (s[i] += 10, 1) : 0;
        if (y.n > m) m = y.n;
        if (!(f = s[0])) {
            --m; for (int i=0; i<m; ++i) s[i] = s[i+1];
        }
    }
    trim();
}
void calc_ln2() {
    for (int i = N*1.048 + .5; i>0; --i)
        ln2.is_zero() ? ln2._div_x(2, 6*i-3) : (ln2.div(9), x._div_x(2, 6*i-3), ln2.add(x));
}
void decimal::ln(decimal& x) {
    q.v[0] = q.n = n = 1; v[0] = q.p = p = q.neg = neg = 0;
    bool f = x.p < 0;
    if (f) u = x, x.div(q, u);
    while ((x.p>0 || (x.p==0 && x.v[0]>=2))) add(ln2), x.div(2);
    z.sub(x, q); x.add(q); q.div(z, x); z.mul(q, q); q.add(q);
    x.v[0] = 0; x.n = 1; x.p = 0; x.neg = 0;
    for (int i=1; ; i+=2) {
        u = q; q.mul(u, z); u.div(i); x.add(u);
        if (u.is_zero()) break;
    }
    add(x);
    if (f) neg = 1;
    trim();
}
void decimal::exp(decimal& x) {
    w.v[0] = y.v[0] = v[0] = 1; w.n = y.n = n = 1; w.p = y.p = p = 0; w.neg = y.neg = neg = 0; z = x;
    while (true) {
        if (z.is_zero()) break;
        add(z); w.add(y); u.mul(z, x); z.div(u, w);
    }
    trim();
}
void decimal::pow(decimal& x, decimal& y) {
    ln(x); x.mul(y, *this); exp(x);
}
void calc_pi_2() {
    x.v[0] = 8; y.v[0] = 2; z.v[0] = w.v[0] = 1; x.n = y.n = z.n = w.n = 1;
    x.p = y.p = z.n = w.n = 0; x.neg = y.neg = 0; z.neg = w.neg = 1; z.div(25); w.div(57121);
    for (int i=1; ; i+=2) {
        u = x; x.mul(u, z); u.div(5*i); q = y; y.mul(q, w); q.div(239*i); c.sub(u, q); pi_2.add(c);
        if (c.is_zero()) return;
    }
}
void decimal::atan(decimal& x) {
    if (x.v[0]==1 && x.n==1 && x.p==0) {
        *this = pi_2; div(2); neg = x.neg;
    } else {
        v[0] = 0; z.v[0] = 1; n = z.n = 1; p = z.p = 0; w.v[0] = 5; w.n = 1; w.p = -1; neg = z.neg = 0;
        if (z.abs_ge(x)) {
            if (w.abs_ge(x)) {
                y.mul(x, x); y.neg = 1;
                for (int i=1; ; i+=2) {
                    q = x; x.mul(q, y); q.div(i); add(q);
                    if (q.is_zero()) return;
                }
            } else {
                c = x; c.div(2); u.mul(x, c); z.add(u); u.div(c, z);
                y.mul(u, u); y.neg = 1;
                for (int i=1; ; i+=2) {
                    q = u; u.mul(q, y); q.div(i); add(q);
                    if (u.is_zero()) break;
                }
                y.mul(c, c); y.neg = 1;
                for (int i=1; ; i+=2) {
                    q = c; c.mul(q, y); q.div(i); add(q);
                    if (c.is_zero()) return;
                }
            }
        } else {
            w.v[0] = 1; w.v[1] = 5; w.n = 2; w.p = 0;
            if (x.abs_ge(w)) {
                add(pi_2); neg = x.neg; y.div(z, x); z.mul(y, y); y.neg = neg^1; z.neg = 1;
                for (int i=1; ; i+=2) {
                    q = y; y.mul(q, z); q.div(i); add(q);
                    if (q.is_zero()) return;
                }
            } else {
                c = x; c.div(2); u.mul(x, c); z.add(u); u.div(c, z);
                y.mul(u, u); y.neg = 1;
                for (int i=1; ; i+=2) {
                    q = u; u.mul(q, y); q.div(i); add(q);
                    if (u.is_zero()) break;
                }
                y.mul(c, c); y.neg = 1;
                for (int i=1; ; i+=2) {
                    q = c; c.mul(q, y); q.div(i); add(q);
                    if (c.is_zero()) return;
                }
            }
        }
    }
}
void decimal::atan2(decimal& y, decimal& x) {
    if (x.is_zero()) {
        *this = pi_2; neg = y.neg;
    } else {
        short nx = x.neg, ny = y.neg && !y.is_zero();
        z.div(y, x); y = z; atan(y);
        if (nx) z.add(pi_2, pi_2), z.neg = ny, add(z);
    }
}
void decimal::sqrt(decimal& x) {
    *this = x; z.v[0] = 0; z.n = 1; z.p = 0; z.neg = 0;
    while(true) {
        w.sub(z, *this); z = *this; u.div(x, *this); add(u); div(2);
        if (w.is_zero()) return;
    }
}
void decimal::asin(decimal& x) {
    if (x.v[0]==1 && x.n==1 && x.p==0) {
        n = pi_2.n; p = pi_2.p;
        for (int i=0; i<pi_2.n; ++i) v[i] = pi_2.v[i];
        return;
    }
    y.v[0] = 1; y.n = 1; y.p = 0; y.neg = 0; z.mul(x, x); c.sub(y, z); q.sqrt(c); y.div(x, q); x = y; atan(x);
}
void decimal::acos(decimal& x) {
    asin(x); y = *this; sub(pi_2, y);
}
void decimal::sin(decimal& x) {
    u = x; y.mul(x, x); w.v[0] = z.v[0] = 1; n = w.n = z.n = 1; p = w.p = z.p = 0; neg = w.neg = z.neg = 0; v[0] = 0;
    while (true) {
        add(u); w.add(z); q.div(u, w); w.add(z); u.div(q, w); q = u; u.mul(q, y); u.neg ^= 1;
        if (u.is_zero()) break;
    }
    trim();
}
void decimal::cos(decimal& x) {
    y.mul(x, x); u.v[0] = z.v[0] = 1; n = u.n = w.n = z.n = 1; p = u.p = w.p = z.p = 0;
    neg = u.neg = w.neg = z.neg = 0; y.neg = 1; v[0] = w.v[0] = 0;
    while (true) {
        add(u); w.add(z); q.div(u, w); w.add(z); u.div(q, w); q = u; u.mul(q, y);
        if (u.is_zero()) break;
    }
    trim();
}
void decimal::tan(decimal& x) {
    sin(x); c.cos(x); y = *this; div(y, c);
}

void solve() {
    x.read();
    if (func[0] == 'a') {
        if (func[1] == 'd') {
            y.read(); r.add(x, y);
        } else if (func[1] == 's') {
            r.asin(x);
        } else if (func[1] == 'c') {
            r.acos(x);
        } else if (func[1] == 't') {
            if (func[4] == '2') {
                y.read(); r.atan2(x, y);
            } else r.atan(x);
        }
    } else if (func[0] == 's') {
        if (func[1] == 'u') {
            y.read(); r.sub(x, y);
        } else if (func[1] == 'q') r.sqrt(x);
        else r.sin(x);
    } else if (func[0] == 'm') {
        y.read(); r.mul(x, y);
    } else if (func[0] == 'd') {
        y.read(); r.div(x, y);
    } else if (func[0] == 'p') {
        y.read(); r.pow(x, y);
    } else if (func[0] == 'e') r.exp(x);
    else if (func[0] == 'l') r.ln(x);
    else if (func[0] == 'c') r.cos(x);
    else r.tan(x);
    cin >> p; r.write(p);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    calc_ln2(); calc_pi_2();
    while (cin >> func) solve();
    return 0;
}