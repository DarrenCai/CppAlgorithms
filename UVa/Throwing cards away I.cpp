/**
 * UVa10935
 * 卡片游戏
 */

#include <iostream>
#include <queue>

int main()
{
    using namespace std;
    int n;
    while(cin>>n && n)
    {
        cout << "Discarded cards:";
        if(n > 1)
        {
            cout << " 1";
        }
        queue<int> q;
        for(int i=2; i<=n; ++i)
        {
            q.push(i);
        }
        while(q.size() > 1)
        {
            int t = q.front();
            q.pop();
            q.push(t);
            cout << ", " << q.front();
            q.pop();
        }
        cout << "\nRemaining card: " << (n>1 ? q.front():1) << endl;
    }
    return 0;
}