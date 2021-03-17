/**
 * UVa10820
 * 交表
 */

#include <iostream>
using namespace std;

#define N 50020
int phi[N] = {0}, d[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=2; i<N; ++i) if (!phi[i])
        for (int j=i; j<N; j+=i) {
            if (!phi[j]) phi[j] = j;
            phi[j] = phi[j]/i*(i-1);
        }
    d[1] = 1;
    for (int i=2; i<N; ++i) d[i] = d[i-1] + (phi[i] << 1);
    int n; while (cin>>n && n) cout << d[n] << endl;
    return 0;
}