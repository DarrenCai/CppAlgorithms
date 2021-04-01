/**
 * UVa10213
 * 多少块土地
 * 本题的大数运算如果用python做（python直接支持大数运算），代码非常简洁：
 * import sys
 * t = int(sys.stdin.readline())
 * for i in range(t):
 *     n = int(sys.stdin.readline())
 *     sys.stdout.writelines([str(n*(n-1)*(n-2)*(n-3)//24+n*(n-1)//2+1)+'\n'])
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    const long long m=1e9, p=1e18;
    short t; cin >> t;
    while (t--) {
        int n; cin >> n;
        if (n > 4) {
            long long t1 = n*(n-1ll)/2, t2 = (n-2ll)*(n-3)/2, t[5];
            long long a = t1/p, b = t1%p/m, c = t1%p%m, t3 = t2/p, t4 = t2%p/m, t5 = t2%p%m;
            t[4] = c*t5%m;
            t[3] = c*t5/m + b*t5 + c*t4;
            t[2] = t[3]/m + a*t5 + b*t4 + c*t3;
            t[3] %= m;
            t[1] = t[2]/m + a*t4 + b*t3;
            t[2] %= m;
            t[0] = t[1]/m + a*t3;
            t[1] = t[1]%m + t[0]%6*m;
            t[0] /= 6;
            t[2] = (t[2] + t[1]%6*m);
            t[1] /= 6;
            t[3] = (t[3] + t[2]%6*m);
            t[2] /= 6;
            t[4] = (t[4] + t[3]%6*m)/6 + c + 1;
            t[3] = t[3]/6 + t[4]/m + b;
            t[4] %= m;
            t[2] += t[3]/m + a;
            t[3] %= m;
            t[1] += t[2]/m;
            t[2] %= m;
            t[0] += t[1]/m;
            t[1] %= m;
            bool ok = false;
            for (short i=0; i<5; ++i) {
                if (ok) {
                    cout << setw(9) << setfill('0') << t[i];
                } else if (t[i]) {
                    cout << t[i]; ok = true;
                }
            }
            cout << endl;
        } else cout << (n<2 ? 1 : 1<<(n-1)) << endl;
    }
    return 0;
}