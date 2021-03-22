/**
 * UVa580
 * 危险的组合
 */

#include <iostream>
using namespace std;

#define N 31
int d[N] = {0};

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=3, p=1; i<N; ++i, p<<=1) d[i] = d[i-1] + d[i-2] + d[i-3] + p;
    short n; while (cin>>n && n) cout << d[n] << endl;
    return 0;
}