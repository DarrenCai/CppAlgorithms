/**
 * ICPC Archive Volumes :: Volume 23 (2300-2399)
 * Regionals 2001 >> Asia - Taejon
 * 2326 - Moving Tables
 */

#include <iostream>
using namespace std;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        short n, a[200]={0}; cin >> n;
        for (short i=0; i<n; ++i) {
            short s, t; cin >> s >> t;
            s = (s-1)>>1; t = (t-1)>>1;
            if (s > t) {short tt=t; t=s; s=tt;}
            for (short j=s; j<=t; ++j) ++a[j];
        }
        short s = a[0];
        for (short i=1; i<200; ++i) if (a[i] > s) s = a[i];
        cout << 10*s << endl;
    }
    return 0;
}