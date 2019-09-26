/**
 * UVa1442
 * 洞穴
 */

#include <iostream>
using namespace std;

#define min(a,b) (a<b ? a:b)
#define max(a,b) (a>b ? a:b)
#define N 1000005
short f[N], c[N], l[N], r[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short k; cin>>k;
    while (k--) {
        int n, i, sum = 0; cin >> n;
        for (i=0; i<n; ++i) cin >> f[i];
        for (i=0; i<n; ++i) cin >> c[i];
        for (l[0]=c[0], i=1; i<n; ++i)
            if (c[i] <= f[i-1] || c[i-1] < f[i]) l[i] = c[i];
            else l[i] = max(f[i], min(l[i-1], min(c[i-1], c[i])));
        for (r[n-1]=c[n-1], i=n-2; i>=0; --i) 
            if (c[i] <= f[i+1] || c[i+1] < f[i]) r[i] = c[i];
            else r[i] = max(f[i], min(r[i+1], min(c[i+1], c[i])));
        for (i=0; i<n; ++i) sum += min(l[i], r[i]) - f[i];
        cout << sum << endl;
    }
    return 0;
}