/**
 * UVa11105
 * H-半素数
 */

#include <iostream>
using namespace std;

#define M 50005
#define N 250025
bool f1[M]={false}, f2[N]={false}; int p[M], c=0, d[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=1; i<112; ++i) if (!f1[i]) for (int j=i, ii; (ii = (i*j<<2) + i + j) < M; ++j) f1[ii] = true;
    for (int i=1; i<M; ++i) if (!f1[i]) p[c++] = i;
    for (int i=0; i<c && p[i]<250; ++i)
        for (int j=i, ii; j<c && (ii = (p[i]*p[j]<<2) + p[i]+p[j]) < N; ++j) f2[ii] = true;
    d[0] = 0;
    for (int i=1; i<N; ++i) d[i] = d[i-1] + f2[i];
    int n;
    while (cin>>n && n) cout << n << ' ' << d[(n-1)>>2] << endl;
    return 0;
}