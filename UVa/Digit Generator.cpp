/**
 * UVa1583
 * 生成元
 */

#include <iostream>

int main()
{
    using namespace std;
    int t;
    cin >> t;
    while(t--)
    {
        int n, g, b=0;
        cin >> n;
        g = n;
        while(g > 0)
        {
            g /= 10;
            ++ b;
        }
        int i = n - 9*b;
        if(i <= 0)
        {
            i = 1;
        }
        bool flag = false;
        while(i < n)
        {
            int j = g = i;
            while(j > 0)
            {
                g += j % 10;
                j /= 10;
            }
            if(g == n)
            {
                flag = true;
                break;
            }
			++ i;
        }
        cout << (flag ? i : 0) << endl;
    }
    return 0;
}