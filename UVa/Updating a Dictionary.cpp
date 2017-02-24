/**
 * UVa12504
 * 更新字典
 */

#include <iostream>
#include <string>
#include <map>
#include <set>

int main()
{
    using namespace std;
    int t;
    cin >> t;
    cin.get();
    while(t--)
    {
        map<string, string> m[2];
        for(int i=0; i<2; ++i)
        {
            string s;
            getline(cin, s);
            int j=1, len=s.length();
            while(j < len)
            {
                int p1 = s.find(':', j);
                int p2 = s.find(',', p1+1);
                if(p1>0)
                {
                    if(p2 == -1)
                    {
                        p2 = len-1;
                    }
                    m[i][s.substr(j, p1-j)] = s.substr(p1+1, p2-p1-1);
                }
                else
                {
                    break;
                }
                j = p2+1;
            }
        }
        set<string> s1, s2, s3;
        for(auto& x: m[1])
        {
            if(!m[0].count(x.first))
            {
                s1.insert(x.first);
            }
        }
        for(auto& x: m[0])
        {
            if(!m[1].count(x.first))
            {
                s2.insert(x.first);
            }
            else if(x.second != m[1][x.first])
            {
                s3.insert(x.first);
            }
        }
        bool empty = true;
        if(!s1.empty())
        {
            cout << '+';
            int count = 0;
            for(const string& s: s1)
            {
                if(count ++)
                {
                    cout << ',';
                }
                cout << s;
            }
            cout << endl;
            empty = false;
        }
        if(!s2.empty())
        {
            cout << '-';
            int count = 0;
            for(const string& s: s2)
            {
                if(count ++)
                {
                    cout << ',';
                }
                cout << s;
            }
            cout << endl;
            empty = false;
        }
        if(!s3.empty())
        {
            cout << '*';
            int count = 0;
            for(const string& s: s3)
            {
                if(count ++)
                {
                    cout << ',';
                }
                cout << s;
            }
            cout << endl;
            empty = false;
        }
        if(empty)
        {
            cout << "No changes" << endl;
        }
        cout << endl;
    }
    return 0;
}