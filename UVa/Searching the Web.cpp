/**
 * UVa1597
 * 在Web中搜索
 */

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

int op(int i)
{
    return isalpha(i) ? tolower(i) : ' ';
}

int main()
{
    using namespace std;
    int n;
    cin >> n;
    cin.get();
    stringstream ss;
    const set<string> filter{"the", "a", "to", "and", "or", "not"};
    vector<vector<string> > docs(n);
    map<string, map<int, set<int> > > buckets;
    for(int i=0; i<n; ++i)
    {
        string line;
        int num = 0;
        while(getline(cin, line) && line!="**********")
        {
            docs[i].push_back(line);
            transform(line.begin(), line.end(), line.begin(), op);
            ss.str(line);
            ss.clear();
            while(ss >> line)
            {
                if(!filter.count(line))
                {
                    buckets[line][i].insert(num);
                }
            }
            ++ num;
        }
    }
    int m;
    cin >> m;
    cin.get();
    while(m--)
    {
        string query;
        getline(cin, query);
        int p;
        bool find = false;
        if(query.find("NOT") == 0)
        {
            const string& word = query.substr(4);
            int count = 0;
            for(int i=0; i<n; ++i)
            {
                if(buckets[word][i].empty())
                {
                    if(count ++)
                    {
                        cout << "----------" << endl;
                    }
                    const int size = docs[i].size();
                    for(int j=0; j<size; ++j)
                    {
                        cout << docs[i][j] << endl;
                    }
                    find = true;
                }
            }
        }
        else if((p=query.find("AND")) > 0)
        {
            const string& word1 = query.substr(0, p-1);
            const string& word2 = query.substr(p+4);
            int count = 0;
            for(int i=0; i<n; ++i)
            {
                if(buckets[word1][i].size() && buckets[word2][i].size())
                {
                    // 注意用vector保存集合计算结果与用set保存集合运算结果的语句的不同之处
                    //vector<int> s(buckets[word1][i].size()+buckets[word2][i].size());     // 一定要初始化vector的容量到足以容纳结果的数量
                    /* auto it = set_union(buckets[word1][i].begin(), buckets[word1][i].end(),
                              buckets[word2][i].begin(), buckets[word2][i].end(), s.begin()); */
                    //s.resize(it-s.begin());   // 容量调整到实际大小
                    set<int> s;
                    set_union(buckets[word1][i].begin(), buckets[word1][i].end(),
                              buckets[word2][i].begin(), buckets[word2][i].end(), inserter(s, s.begin()));
                    bool flag = false;
                    for(const int j: s)
                    {
                        if(!flag)
                        {
                            if(count ++)
                            {
                                cout << "----------" << endl;
                            }
                        }
                        cout << docs[i][j] << endl;
                        flag = true;
                        find = true;
                    }
                }
            }
        }
        else if((p=query.find("OR")) > 0)
        {
            const string& word1 = query.substr(0, p-1);
            const string& word2 = query.substr(p+3);
            int count = 0;
            for(int i=0; i<n; ++i)
            {
                set<int> s;
                set_union(buckets[word1][i].begin(), buckets[word1][i].end(),
                          buckets[word2][i].begin(), buckets[word2][i].end(), inserter(s, s.begin()));
                bool flag = false;
                for(const int j: s)
                {
                    if(!flag)
                    {
                        if(count ++)
                        {
                            cout << "----------" << endl;
                        }
                    }
                    cout << docs[i][j] << endl;
                    flag = true;
                    find = true;
                }
            }
        }
        else
        {
            int count = 0;
            for(int i=0; i<n; ++i)
            {
                bool flag = false;
                for(const int j: buckets[query][i])
                {
                    if(!flag)
                    {
                        if(count ++)
                        {
                            cout << "----------" << endl;
                        }
                    }
                    cout << docs[i][j] << endl;
                    flag = true;
                    find = true;
                }
            }
        }
        if(!find)
        {
            cout << "Sorry, I found nothing." << endl;
        }
        cout << "==========" << endl;
    }
    return 0;
}