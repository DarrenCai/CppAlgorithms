/**
 * UVa10934
 * 装满水的气球
 */

#include <iostream>
using namespace std;

const unsigned long long M = 1ull<<63;

short log(unsigned long long n) {
    unsigned long long low = 1, high = 63, mid;
    while (low <= high) {
        mid = (low + high) >> 1;
        n >= 1ull<<mid ? low = mid + 1 : high = mid - 1;    // 需要注意unsigned long long的位运算要给1跟上ull
    }
    return low;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short k; unsigned long long n;
    while (cin >> k >> n && k) {
        if (n >= M) {
            cout << "More than 63 trials needed." << endl;
        } else {
            short low = log(n), high = 63, mid;
            if (k < low) while (low <= high) {
                mid = (low + high) >> 1;
                unsigned long long s = mid, v = mid;
                for (short i=1; i<k; ++i) {
                    unsigned long long r = v % (i+1);
                    v = v/(i+1)*(mid-i) + r*(mid-i)/(i+1);      // 要考虑乘法可能溢出
                    s += v;
                }
                if (s == n) high = mid - 1, low = mid;
                else if (s > n) high = mid - 1;
                else low = mid + 1;
            }
            if (low > 63) {
                cout << "More than 63 trials needed." << endl;
            } else cout << low << endl;
        }
    }
    return 0;
}