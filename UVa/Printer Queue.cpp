/**
 * UVa12100
 * 打印队列
 */

#include <iostream>
#include <queue>

int main()
{
    using namespace std;
    int t;
    cin >> t;
    while(t--)
    {
        int n, m;
        cin >> n >> m; 
        vector<int> v;
        priority_queue<int> p;
        while(n--)
        {
            int t;
            cin >> t;
            v.push_back(t);
            p.push(t);
        }
        int i=0, t=0;
        while(i<=m)
        {
            while(i<m)
            {
                if(p.top() == v[i])
                {
                    ++ t;
                    p.pop();
                }
                else
                {
                    v.push_back(v[i]);
                }
                ++ i;
            }
            if(p.top() == v[i])
            {
                cout << ++t << endl;
                break;
            }
            else
            {
                m = v.size();
                v.push_back(v[i]);    
            }
            ++ i;
        }
    }
    return 0;
}