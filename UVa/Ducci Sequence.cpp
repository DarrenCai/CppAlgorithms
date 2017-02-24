/**
 * UVa1594
 * Ducci序列
 * 本题也许可以当数学题做，有一个结论：当元组中的数是奇数个时，只有一开始元组中每个数都相等才最终全0，否则必然Loop。
 * 当元组中的数是偶数个时，复杂很多，但也有规律，我这里猜测2^k个数时必然最终全0，还可以分析等差交替、奇偶交替的情形……
 */

#include <iostream>
#include <vector>
#include <set>

#define abs(a, b) (a>b ? a-b:b-a)

int main()
{
    using namespace std;
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        vector<int> d(n);
        set<vector<int> > s;
        for(int i=0; i<n; ++i)
        {
            cin >> d[i];
        }
        bool bZero=false, bLoop=false;
        while(!bZero && !bLoop)
		{
            bool flag = true;
            for(int i=0; flag && i<n; ++i)
            {
                if(d[i])
                {
                    flag = false;
                }
            }
            if(flag)
            {
                bZero = true;
                continue;
            }
			s.insert(d);
			vector<int> d1(d);
            for(int i=0; i<n-1; ++i)
            {
                d[i] = abs(d1[i], d1[i+1]);
            }
            d[n-1] = abs(d1[n-1], d1[0]);
            if(s.count(d))
            {
                bLoop = true;
            }
        }
        cout << (bZero ? "ZERO":"LOOP") << endl;
    }
    return 0;
}