/**
 * UVa10391
 * 复合词
 */

#include <iostream>
#include <string>
#include <vector>
#include <set>

int main()
{
    using namespace std;
    vector<set<string> > p(26, set<string>());
    string s;
    while(cin >> s)
    {
        p[s[0]-'a'].insert(s);
    }
    for(int i=0; i<26; ++i)
    {
        if(p[i].size() > 1)
        {
            set<string>::iterator iter = p[i].begin();
            for(++iter; iter!=p[i].end(); ++iter)
            {
                for(auto iter1=p[i].begin(); iter1!=iter; ++iter1)
                {
                    const string& s1 = *iter;
                    const string& s2 = *iter1;
                    if(s1.find(s2)==0)
                    {
                        s = s1.substr(s2.length());
                        if(p[s[0]-'a'].count(s))
                        {
                            cout << s1 << endl;
                            break;
                        }
                    }
                }
            }
        }
    }
    return 0;
}