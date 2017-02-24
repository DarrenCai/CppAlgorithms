/**
 * UVa1584
 * 环状序列
 */

#include <iostream>
#include <string>

int main()
{
    using namespace std;
    int t;
    cin >> t;
    while(t--)
    {
        string s;
        cin >> s;
        int n = s.length(), min = 0;
        for(int i=1, j; i<n; ++i)
        {
            for(j=0; j<n && s[(i+j)%n] == s[(min+j)%n]; ++j);
            if(s[(i+j)%n] < s[(min+j)%n])
            {
                min = i;
            }
        }
        for(int i=0; i<n; ++i)
        {
            cout << s[(min+i)%n];
        }
        cout << endl;
    }
    return 0;
}