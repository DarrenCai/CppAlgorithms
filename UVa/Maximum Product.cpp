/**
 * UVa11059
 * 最大乘积
 */

#include <iostream>

int main()
{
    using namespace std;
    int k=0; short n, s[18];
    while(cin>>n) {
        for(short i=0; i<n; ++i)
            cin >> s[i];
        long long max = 0;
        for(short i=0; i<n; ++i) {
            for(short j=i; j<n; ++j) {
                long long p = s[i];
                for(short t=i+1; t<=j; ++t)
                    p *= s[t];
                if (p > max) max = p;
            }
        }
        cout << "Case #" << ++k << ": The maximum product is " << max << '.' << endl << endl;
    }
    return 0;
}