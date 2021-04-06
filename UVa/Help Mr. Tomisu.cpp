/**
 * UVa11440
 * 帮帮Tomisu
 */

#include <iostream>
#include <cmath>
using namespace std;

#define N 10000001
#define M 100000007
bool flag[N] = {false}; int d[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int k = sqrt(N);
    for (int i=2; i<=k; ++i) if (!flag[i])
        for (int j=i*i; j<N; j+=i) flag[j] = true;
    d[1] = 1;
    for (long long m=2; m<N; ++m) d[m] = d[m-1]*(flag[m] ? m : m-1) % M;
    int n, m;
    while (cin>>n>>m && n) {
        long long ans = d[m];
        for (int i=m+1; i<=n; ++i) ans = ans * i % M;
        cout << (ans+M-1)%M << endl;
    }
    return 0;
}