/**
 * UVa400
 * Unix ls命令
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    using namespace std;
    int n;
    while(cin >> n)
    {
        int m=0;
        vector<string> s(n);
        for(int i=0; i<n; ++i)
        {
            cin >> s[i];
            const int len = s[i].length();
            if(len > m)
            {
                m = len;
            }
        }
        sort(s.begin(), s.end());
        const int c = 62/(m+2);
        const int r = (n+c-1)/c;
        cout << "------------------------------------------------------------" << endl;
        for(int i=0; i<r; ++i)
        {
            for(int j=0; j<c; ++j)
            {
                const int t = j*r+i;
                if(t<n)
                {
                    const int len = s[t].length();
                    if(j<c-1)
                    {
                        s[t].append(m+2-len, ' ');
                    }
                    cout << s[t];
                }
            }
            cout << endl;
        }
    }
    return 0;
}