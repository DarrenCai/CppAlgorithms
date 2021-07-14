/**
 * UVa1651
 * 二元运算
 */

#include <iostream>
using namespace std;

short op[10][10];
struct info{short s, p, v[11];} d[10][10];

void period(short x, short y) {
    info& ref = d[x][y]; ref.v[0] = x;
    short t = 1, v = x;
    while (true) {
        v = op[v][y];
        for (short i=1; i<t; ++i) if (v == ref.v[i]) {
            ref.p = t-i;
            ref.s = i;
            return;
        }
        ref.v[t++] = v;
    }
}

short get(short x, short y, long long c) {
    const info& ref = d[x][y];
    return ref.v[c <= ref.s ? c : (c-ref.s) % ref.p + ref.s];
}

short firstBit(short v, long long c) {
    short his[10], t = 0;
    for (short i=v; ++i<10 && c; --c) v = op[v][i];
    while (c) {
        his[t++] = v;
        for (short i=0; i<10 && c; ++i, --c) v = op[v][i];
        if (c == 0) return v;
        for (short i=0; i<t; ++i) if (v == his[i]) {
            v = his[i + c % (10*(t-i)) / 10];
            for (short i=0, p=c%10; p--; ++i) v = op[v][i];
            return v;
        }
    }
    return v;
}

short bit(long long a, long long b, long long p) {
    short x = a/p%10; long long c = p + a/p*p - 1;
    short v = get(x, x, min(b, c)-a), his[10], t = 0;
    while (b > c) {
        his[t++] = v;
        for (short i=1; i<11; ++i) {
            v = get(v, (x+i)%10, min(p, b-c));
            if (b <= (c += p)) return v;
        }
        for (short i=0; i<t; ++i) if (v == his[i]) {
            v = his[i + (b-c) % (10*p*(t-i)) / (10*p)];
            c = (b-c) % (10*p);
            for (short i=1; i<11; ++i) {
                v = get(v, (x+i)%10, min(p, c));
                if ((c-=p) <= 0) return v;
            }
        }
    }
    return v;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    unsigned long long p[19]; p[0] = 1; for (short i=1; i<19; ++i) p[i] = 10*p[i-1];
    while (true) {
        for (short i=0; i<10; ++i) for (short j=0; j<10; ++j) if (!(cin >> op[i][j])) return 0;
        long long a, b; cin >> a >> b;
        if (a < b) {
            for (short x=0; x<10; ++x) for (short y=0; y<10; ++y) period(x, y);
            unsigned long long v = firstBit(a%10, b-a);
            for (short i=1; i<19; ++i) {
                if (b < p[i]) break;
                v += bit(a, b, p[i])*p[i];
            }
            cout << v << endl;
        } else cout << a << endl;
    }
    return 0;
}
