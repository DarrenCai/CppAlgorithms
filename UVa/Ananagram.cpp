/**
 * UVa156
 * 反片语
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

int main()
{
    vector<string> words;
    map<string, int> count;
    string s;
    while(cin>>s && s!="#")
    {
        words.push_back(s);
        string key = s;
        transform(key.begin(), key.end(), key.begin(), (int (*)(int))tolower);
        sort(key.begin(), key.end());
        auto iter = count.find(key);
        if(iter != count.end())
        {
            iter->second ++;     // 注意.和++的优先级一样，结合顺序是从左到右
        }
        else
        {
            count[key] = 1;
        }
    }
    set<string> ans;
    const int len = words.size();
    for(int i=0; i<len; ++i)
    {
        string key = words[i];
        transform(key.begin(), key.end(), key.begin(), (int (*)(int))tolower);
        sort(key.begin(), key.end());
        if(count[key] == 1)
        {
            ans.insert(words[i]);
        }
    }
    for(auto iter=ans.begin(); iter!=ans.end(); ++iter)
    {
        cout << *iter << endl;
    }
    return 0;
}