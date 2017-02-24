/**
 * UVa540
 * 团体队列
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

int main()
{
    using namespace std;
    int k=0;
    short t;
    while(cin>>t && t)
    {
        cout << "Scenario #" << ++k << endl;
        map<int, short> teamNO;
        queue<short> teamOrder;
        for(short i=0; i<t; ++i)
        {
            short n;
            cin >> n;
            while(n--)
            {
                int e;
                cin >> e;
                teamNO[e] = i;
            }
        }
        vector<queue<int> > longTeam(t);
        string cmd;
        while(cin>>cmd && cmd[0]!='S')
        {
            if(cmd[0]=='E')
            {
                int x;
                cin >> x;
                if(longTeam[teamNO[x]].empty())
                {
                    teamOrder.push(teamNO[x]);
                }
                longTeam[teamNO[x]].push(x);
            }
            else
            {
                int x = longTeam[teamOrder.front()].front();
                longTeam[teamOrder.front()].pop();
                if(longTeam[teamOrder.front()].empty())
                {
                    teamOrder.pop();
                }
                cout << x << endl;
            }
        }
        cout << endl;
    }
    return 0;
}