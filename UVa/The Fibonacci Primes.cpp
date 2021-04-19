/**
 * UVa10236
 * 斐波那契质数
 * 要用到公式：gcd(F[n],F[m])=F[gcd(n,m)] => n|m <=> F(n)|F(m)
 * 参见
 *      https://blog.csdn.net/qq_37919863/article/details/78905198
 *      https://www.cnblogs.com/1024th/p/10897313.html
 *      https://www.cnblogs.com/Milkor/p/4734763.html
 */

#include <iostream>
using namespace std;

#define M 253010
#define N 22221
bool flag[M] = {false}; int idx[N]; long double fp[M];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=2; i<503; ++i) if (!flag[i]) for (int j=i*i; j<M; j+=i) flag[j] = true;
    flag[4] = false;
    for (int i=3, c=1; i<M && c<N; ++i) if (!flag[i]) idx[c++] = i;
    fp[3] = 2.; fp[4] = 3.;
    for (int i=5, f=0; i<=idx[N-1]; ++i) {
        fp[i] = fp[i-1] + (f ? fp[i-2]/10 : fp[i-2]);
        if (f = fp[i] >= 1.e9) fp[i] /= 10;
    }
    int n;
    while (cin >> n) cout << int(fp[idx[n]]) << endl;
    return 0;
}