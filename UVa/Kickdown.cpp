/**
 * UVa1588
 * 换低挡装置
 */

#include <iostream>
#include <string>

#define max(a, b) (a>b ? a:b)
#define min(a, b) (a<b ? a:b)

int main()
{
    using namespace std;
    string s1, s2;
    while(cin >> s1 >> s2)
    {
        const int len1 = s1.length();
        const int len2 = s2.length();
        int min = len1 + len2;
        for(int i=0; i<len2; ++i)
        {
            bool flag = true;
            for(int j=0; flag && j+i<len2 && j<len1; ++j)
            {
                if(s1[j]-'0' + s2[j+i]-'0' > 3)
                {
                    flag = false;
                }
            }
            if(flag)
            {
                min = i + max(len1, len2-i);
                break;
            }
        }
        for(int i=1; i<len1; ++i)
        {
            bool flag = true;
            for(int j=0; flag && j+i<len1 && j<len2; ++j)
            {
                if(s2[j]-'0' + s1[j+i]-'0' > 3)
                {
                    flag = false;
                }
            }
            if(flag)
            {
                min = min(i + max(len2, len1-i), min);
                break;
            }
        }
        cout << min << endl;
    }
    return 0;
}