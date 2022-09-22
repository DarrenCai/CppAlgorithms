/**
 * UVa1414/LA4050
 * 汉诺塔
 * NEERC 2007
 */

#include <iostream>
using namespace std;

#define N 32
#define M 720
struct node {long long v; short s;} d[M][N][3]; short e[] = {120, 24, 6, 2, 1, 1}, p[M][6], a[6], n;
short s[][2] = {{1, 2}, {0, 2}, {0, 1}}, x[][3] = {{-1, 0, 1}, {2, -1, 3}, {4, 5, -1}};

short cantor() {
    short c[6] = {0}, v = 0;
    for (short i=5; i>=0; --i) {
        short s = 0;
        for (short x=a[i]; x>0; x -= x&(-x)) s += c[x];
        v += s * e[i];
        for (short x=a[i]+1; x<6; x += x&(-x)) ++c[x];
    }
    return v;
}

void decantor(short x, short (&a)[6]) {
    bool f[6] = {false};
    for (short i=0; i<6; ++i) {
        short v = x/e[i];
        for (short j=0, t=0; j<6; ++j) if (!f[j]) {
            if (t++ == v) {
                f[a[i] = j] = true;
                break;
            }
        }
        x %= e[i];
    }
}

void init() {
    for (short m=0; m<M; ++m) {
        decantor(m, p[m]);
        for (short i=0; i<3; ++i) for (short j=0; j<6; ++j) if (p[m][j]>>1 == i) {
            d[m][1][i].v = 1; d[m][1][i].s = s[i][p[m][j]-(i<<1)];
            break;
        }
        for (short n=2; n<N; ++n) for (short i=0; i<3; ++i) {
            const node &t1 = d[m][n-1][i], &t2 = d[m][n-1][t1.s];
            d[m][n][i].v = t1.v + 1 + t2.v;
            d[m][n][i].s = 3-i-t1.s;
            if (t2.s != d[m][n][i].s) {
                d[m][n][i].v += 1 + t1.v;
                d[m][n][i].s = t1.s;
            }
        }
    }
}

long long solve() {
    char s[3];
    for (short i=0, j; i<6; ++i) {
        cin >> s;
        a[i] = x[s[0]-'A'][s[1]-'A'];
    }
    return d[cantor()][n][0].v;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    init();
    while (cin >> n) cout << solve() << endl;
    return 0;
}