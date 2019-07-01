/**
 * UVa11054
 * Gergovia的酒交易
 */

#include <iostream>
using namespace std;

#define N 50010
struct village {
    int p; short a;
};
village buy[N], sale[N];

int main()
{
    int n;
    while (cin >> n && n) {
        long long t = 0; int h1=0, t1=0, h2=0, t2=0; short a;
        for (int i=0; i<n; ++i) {
            cin >> a;
            if (a > 0) {
                while (h1 < t1) {
                    village &v = sale[h1];
                    a += v.a;
                    if (a < 0) {
                        t -= (v.a - a) * (i - v.p); v.a = a;
                        break;
                    } else {
                        t -= v.a * (i - v.p); h1 ++;
                    }
                }
                if (a > 0) buy[t2].p = i, buy[t2 ++].a = a;
            } else {
                while (h2 < t2) {
                    village &v = buy[h2];
                    a += v.a;
                    if (a > 0) {
                        t += (v.a - a) * (i - v.p); v.a = a;
                        break;
                    } else {
                        t += v.a * (i - v.p); h2 ++;
                    }
                }
                if (a < 0) sale[t1].p = i, sale[t1 ++].a = a;
            }
        }
        cout << t << endl;
    }
    return 0;
}