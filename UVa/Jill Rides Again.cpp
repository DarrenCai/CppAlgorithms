/**
 * UVa507
 */

#include <iostream>

int main()
{
    using namespace std;
    short k=0, t; cin >> t;
    while (k++ < t) {
        int sum = 0, max = -1; short s1 = 1, s2 = 1, e = 1, n; cin >> n;
        for (short i=1; i<n; ++i) {
            if (sum < 0) sum = 0, s2 = i;
            short a; cin >> a; sum += a;
            if (sum > max || (sum==max && (i-s2 > e - s1)))
                s1 = s2, e = i, max = sum;
        }
        if (max > 0) {
            cout << "The nicest part of route " << k << " is between stops " << s1 << " and " << e+1 << endl;
        } else {
            cout << "Route " << k << " has no nice parts" << endl;
        }
    }
    return 0;
}