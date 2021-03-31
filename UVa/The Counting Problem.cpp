/**
 * UVa1640
 * 统计问题
 */

#include <iostream>
using namespace std;

int p[]={1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 100000000};

void calc(int x, short n, int (&c)[10]) {
    if (n==0) return;
    short v = x/p[n-1];
    x -= v*p[n-1];
    c[v] += x+1;
    calc(x, n-1, c);
    if (n>1) for (short i=0; i<10; ++i) c[i] += v*(n-1)*p[n-2];
    for (short i=0; i<v; ++i) c[i] += p[n-1];
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int a, b;
    while (cin>>a>>b && a && b) {
        if (a > b) {
            int t = a; a = b; b = t;
        }
        --a;
        int c1[10] = {0}, c2[10] = {0};
        for (short i=1; i<10; ++i) if (p[i] > a) {
            calc(a, i, c1);
            for (short j=1; j<i; ++j) c1[0] -= p[j];
            break;
        }
        for (short i=1; i<10; ++i) if (p[i] > b) {
            calc(b, i, c2);
            for (short j=1; j<i; ++j) c2[0] -= p[j];
            break;
        }
        for (short i=0; i<10; ++i) cout << c2[i]-c1[i] << (i<9 ? ' ' : '\n');
    }
    return 0;
}