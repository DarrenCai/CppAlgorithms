/**
 * UVa401
 * 回文镜像串,要注意字符串取一半的处理（一定要不小于一半）
 */

#include <iostream>
#include <string>

int main()
{
    const char* mirror = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";
    using namespace std;
    string s;
    while(cin >> s)
    {
        const int len = s.length();
        bool mirrored = true, palindrome = true;
        for(int i=0; i<(len+1)>>1 && (mirrored || palindrome); ++i)
        {
            if(palindrome && s[i] != s[len-i-1])
            {
                palindrome = false;
            }
            if(mirrored)
            {
                if(s[i] >= 'A' && s[i] <= 'Z')
                {
                    if(s[len-i-1] != mirror[s[i]-'A'])
                    {
                        mirrored = false;
                    }
                }
                else
                {
                    if(s[len-i-1] != mirror[s[i]-'1'+26])
                    {
                        mirrored = false;
                    }
                }
            }
        }
        if(mirrored && palindrome)
        {
            cout << s << " -- is a mirrored palindrome.\n\n";
        }
        else if(mirrored)
        {
            cout << s << " -- is a mirrored string.\n\n";
        }
        else if(palindrome)
        {
            cout << s << " -- is a regular palindrome.\n\n";
        }
        else
        {
            cout << s << " -- is not a palindrome.\n\n";
        }
    }
    return 0;
}