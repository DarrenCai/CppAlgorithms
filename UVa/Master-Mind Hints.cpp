/**
 * UVa 340
 * 猜数字游戏的提示
 */

#include <iostream>

int main()
{
    using namespace std;
    int n, game = 0;
    while(cin>>n && n)
    {
        const int N = n;
        int ans[N], count[10] = { 0 };
        for(int i=0; i<n; ++i)
        {
            cin >> ans[i];
            ++ count[ans[i]];
        }
        cout << "Game " << ++game << ':' << endl;
        while(true)
        {
            bool allZ = true;
            int counta[10], countb[10] = { 0 }, total = 0, appear = 0;
            for(int i=0; i<10; ++i)
            {
                counta[i] = count[i];
            }
            for(int i=0; i<n; ++i)
            {
                int guess;
                cin >> guess;
                if(guess == ans[i])
                {
                    ++ total;
                    -- counta[guess];
                }
                else
                {
                    ++ countb[guess];
                }
                if(guess)
                {
                    allZ = false;
                }
            }
            if(allZ)
            {
                break;
            }
            for(int i=0; i<10; ++i)
            {
                appear += counta[i] < countb[i] ? counta[i] : countb[i];
            }
            cout << "    (" << total << ',' << appear << ')' << endl;
        };
    }
    return 0;
}