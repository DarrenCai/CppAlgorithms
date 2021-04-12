/**
 * UVa1210
 * 连续素数之和
 */

#include <iostream>
using namespace std;

#define N 10010
#define C 1300
bool flag[N] = {false}; short prim[C], c=0; int d[N] = {0};

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (short i=2; i<100; ++i) for (short j=i*i; j<N; j+=i) flag[j] = true;
    for (short i=2; i<N; ++i) if (!flag[i]) prim[c++] = i;
    for (short i=1; i<67; ++i) {
        short s = 0; for (short j=0; j<i; ++j) s += prim[j]; ++ d[s];
        for (short j=1, jj=c-i; j<=jj; ++j) {
            if ((s += prim[j+i-1]-prim[j-1]) >= N) break;
            ++ d[s];
        }
    }
    short n;
    while (cin>>n && n) cout << d[n] << endl;
    return 0;
}