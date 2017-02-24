/**
 * UVa12096
 * 集合栈计算机
 * 为每个不同的集合分配一个唯一的ID，则每个集合都可以表示成所包含元素的ID集合
 */

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <set>
#include <map>
#include<algorithm>

#define ID(x)   \
    IDcache.count(x) ? IDcache[x] :     \
    (Setcache.push_back(x),      \
    IDcache[x] = Setcache.size() - 1)   \

int main()
{
    using namespace std;
    typedef set<int> Set;

    int t;
    cin >> t;
    while(t--)
    {
        map<Set,int> IDcache;   //把集合映射成ID
        vector<Set> Setcache;   //根据ID取集合
        stack<int> s;           //题目中的栈
        int n;
        cin >> n;
        while(n--)
        {
            string cmd;
            cin >> cmd;
            if(cmd[0] == 'P')
            {
                s.push(ID(Set()));
            }
            else if(cmd[0] == 'D')
            {
                s.push(s.top());
            }
            else
            {
                Set x1 = Setcache[s.top()];
                s.pop();
                Set x2 = Setcache[s.top()];
                s.pop();
                Set x;
                if(cmd[0] == 'U')
                {
                    set_union(x1.begin(), x1.end(), x2.begin(), x2.end(), inserter(x,x.begin()));
                }
                if(cmd[0] == 'I')
                {
                    set_intersection(x1.begin(), x1.end(), x2.begin(), x2.end(), inserter(x,x.begin()));
                }
                if(cmd[0] == 'A')
                {
                    x = x2;
                    x.insert(ID(x1));
                }
                s.push(ID(x));
            }
            cout << Setcache[s.top()].size() << endl;
        }
        cout << "***" << endl;
    }
    return 0;
}