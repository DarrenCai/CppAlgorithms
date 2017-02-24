/**
 * UVa10082
 */

#include <iostream>

int main()
{
    using namespace std;
    const char* s = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
    char i, c;
    while(cin.get(c))
    {
        for(i=1; s[i] && s[i]!=c; ++i);
        if(s[i])
        {
            cout << s[i-1];
        }
        else
        {
            cout << c;
        }
    }
    return 0;
}