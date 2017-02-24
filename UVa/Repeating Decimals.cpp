/**
 * UVa202
 * 循环小数
 */

#include <iostream>
#include <string>
#include <vector>

int main()
{
    using namespace std;
    int m, n;
    while(cin >> m >> n)
    {
        cout << m << '/' << n << " = " << m/n << '.';
        int p = 0;
        string s;
        vector<int> r;
        m %= n;
        while(m && !p)
        {
            r.push_back(m);
            m *= 10;
            s += '0' + m/n;
            m %= n;
            const int len = r.size();
            for(int i=0; i<len; ++i)
            {
                if(r[i] == m)
                {
                    p = i+1;
                    break;
                }
            }
        }
        for(int i=0; i<p-1; ++i)
        {
            cout << s[i];
        }
        if(s.length() && !p)
        {
            cout << s;
        }
        cout << '(';
        int t = s.length()-p+1;
        if(p)
        {
            int len = s.length();
            if(len > 50)
            {
                len = 50;
            }
            for(int i=p-1; i<len; ++i)
            {
                cout << s[i];
            }
            if(s.length() > 50)
            {
                cout << "...";
            }
        }
        else
        {
            t = 1;
            cout << 0;
        }
        cout << ")\n   " << t << " = number of digits in repeating cycle\n" << endl;
    }
    return 0;
}