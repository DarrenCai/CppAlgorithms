/**
 * UVa10815
 * 安迪的第一个字典
 */

#include <iostream>
#include <string>
#include <sstream>
#include <set>

int main()
{
    using namespace std;
    set<string> dict;
    string s;
    while(cin >> s)
    {
        const int len = s.length();
        for(int i=0; i<len; ++i)
        {
            s[i] = isalpha(s[i]) ? tolower(s[i]) : ' ';
        }
        stringstream ss(s);
        while(ss >> s)
        {
            dict.insert(s);
        }
    }
    for(set<string>::iterator iter=dict.begin(); iter!=dict.end(); ++iter)
    {
        cout << *iter << endl;
    }
    return 0;
}