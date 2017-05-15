/**
 * UVa10340
 * 子序列
 */

#include <iostream>
#include <string>


int main()
{
    using namespace std;
    string s, t;
    while(cin >> s >> t)
    {
        const int lens = s.length();
        const int lent = t.length();
        int i, j, p=0, flag=1;
        for(i=0; flag && i<lens; ++i)
        {
            for(j=p; j<lent; ++j)
            {
                if(s[i] == t[j])
                {
                    p = j+1;
                    break;
                }
            }
            if(j == lent)
            {
                flag = 0;
            }
        }
        cout << (flag ? "Yes" : "No")<< endl;
    }
    return 0;
}