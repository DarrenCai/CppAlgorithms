/**
 * UVa1591
 * 数据挖掘
 */

#include <iostream>

int main()
{
    using namespace std;
    int n, p, q;
    while(cin >> n >> p >> q)
    {
        int a=0, b=0;
        unsigned long long k = n*q;
        if(n>1)
        {
            k = (long long)1<<63;
            for(int i=0, j; i<32; ++i)
            {
                for(int j=0; j<32; ++j)
                {
                    if(p*(1+((long long)1<<i))>>j >= q)
                    {  
                        unsigned long long t = (p*(n-1)*(1+((long long)1<<i))>>j)+q;
                        if(t < k)
                        {
                            k = t;
                            a = i;
                            b = j;
                        }
                    }
                }
            }
        }
        cout << k << ' ' << a << ' ' << b << endl;;
    }
    return 0;
}