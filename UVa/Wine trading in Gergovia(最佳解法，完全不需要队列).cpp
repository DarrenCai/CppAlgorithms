/**
 * UVa11054
 * Gergovia的酒交易
 */

#include <iostream>
using namespace std;

int main()
{
    int n;
    while (cin >> n && n) {
        long long t = 0, a=0; short c;
        for (int i=0; i<n; ++i) {
            cin >> c;
            a > 0 ? t += a : t -= a;
            a += c;
        }
        cout << t << endl;
    }
    return 0;
}