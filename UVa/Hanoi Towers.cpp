/**
 * UVa1414
 * 汉诺塔
 */

#include <iostream>
using namespace std;

#define N 32
struct status {short p; long long v;} d[720][N][3];
short p[720][6], a[6], v[] = {120, 24, 6, 2, 1, 1}; char s[3];

short encode() {
    short n = 0;
    for (short i=0, j, k; i<5; ++i) {
        for (j=0, k=i+1; k<6; ++k) if (a[k] <  a[i]) ++j;
        n += j*v[i];
    }
    return n;
}

void decode(short n, short (&a)[6] = ::a) {
    bool visit[6] = {false};
    for (short i=0; i<6; n %= v[i++]) {
        short j = n/v[i];
        for (short k=0; k<=j; ++k) if (visit[k]) ++j;
        visit[a[i] = j] = true;
    }
}

short choose(short a1, short a2, short (&a)[6] = ::a) {
    for (short i=0; i<6; ++i) {
        if (a[i] == a1) return a1;
        if (a[i] == a2) return a2;
    }
    return -1;
}

short step(short c) {
    return c==2 || c==4 ? 0 : (c==0 || c==5 ? 1 : 2);
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (short i=0; i<720; ++i) {
        decode(i, p[i]);
        for (short j=0; j<3; ++j) {
            d[i][1][j].p = step(choose(j<<1, (j<<1)+1, p[i]));
            d[i][1][j].v = 1;
        }
    }
    for (short i=0; i<720; ++i) for (short n=2; n<N; ++n) for (short j=0; j<3; ++j) {
        status s = d[i][n-1][j];
        short c = choose(j<<1, (j<<1)+1, p[i]), pp = step(c); long long cnt = s.v;
        if (pp == s.p) pp = step((j<<2)+1-c);
        status ss = d[i][n-1][s.p];
        while (ss.p != pp) {
            cnt += 1 + ss.v;
            pp = s.p;
            s = ss;
            ss = d[i][n-1][s.p];
        }
        d[i][n][j].p = pp;
        d[i][n][j].v = cnt + 1 + ss.v;
    }
    short n;
    while (cin >> n) {
        for (short i=0; i<6; ++i) {
            cin >> s;
            if (s[0] == 'A') {
                a[i] = s[1] == 'B' ? 0 : 1;
            } else if (s[0] == 'B') {
                a[i] = s[1] == 'A' ? 2 : 3;
            } else a[i] = s[1] == 'A' ? 4 : 5;
        }
        cout << d[encode()][n][0].v << endl;
    }
    return 0;
}