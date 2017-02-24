/**
 * UVa253
 * 骰子涂色
 */

#include <iostream>
#include <string>

int main()
{
    using namespace std;
    // 按照题意编号规则情况下，枚举所有旋转的可能结果（只记录最终的上、前、左三个面的编号就行了，与它们正对的三个面编号用5减一下就能得出）
    const char table[24][3] = { {0, 1, 2}, {0, 2, 4}, {0, 3, 1}, {0, 4, 3},
                                {1, 0, 3}, {1, 2, 0}, {1, 3, 5}, {1, 5, 2},
                                {2, 0, 1}, {2, 1, 5}, {2, 4, 0}, {2, 5, 4},
                                {3, 0, 4}, {3, 1, 0}, {3, 4, 5}, {3, 5, 1},
                                {4, 0, 2}, {4, 2, 5}, {4, 3, 0}, {4, 5, 3},
                                {5, 1, 3}, {5, 2, 1}, {5, 3, 4}, {5, 4, 2} };
    string s;
    while(cin >> s)
    {
        bool diff = true;
        string ss = s.substr(6, 6);
        s.erase(6);
        for(char i=0; diff && i<24; ++i)
        {
            char top = table[i][0];
            char front = table[i][1];
            char left = table[i][2];
            if( s[top]==ss[0] && s[5-top]==ss[5]
                && s[front]==ss[1] && s[5-front]==ss[4]
                && s[left]==ss[2] && s[5-left]==ss[3] )
            {
                diff = false;
            }
        }
        cout << (diff ? "FALSE":"TRUE") << endl;
    }
    return 0;
}