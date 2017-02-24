/**
 * UVa1595
 * 对称轴
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

int main()
{
    using namespace std;
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        map<int, vector<int> > p;
        while(n--)
        {
            int x, y;
            cin >> x >> y;
            p[y].push_back(x);
        }
        map<int, vector<int> >::iterator iter;
        for(iter=p.begin(); iter!=p.end(); ++iter)
        {
            vector<int>& v = iter->second;
            sort(v.begin(), v.end());
        }
        iter = p.begin();        
        bool flag = true;
        const int s = iter->second[0] + iter->second[iter->second.size()-1];
        while(flag && iter!=p.end())
        {
            vector<int>& v = iter->second;
            const int size = v.size();
            const int half = size+1 >> 1;
            for(int i=0; flag && i<half; ++i)
            {
                if(v[i]+v[size-1-i] != s)
                {
                    flag = false;
                }
            }
            ++ iter;
        }
        cout << (flag ? "YES":"NO") << endl;
    }
    return 0;
}