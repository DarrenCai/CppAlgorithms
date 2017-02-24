/**
 * UVa227
 * 谜题
 */

#include <iostream>

int main()
{
    using namespace std;
    int count = 0;
    while(true)
    {
        char s[5][6];
        int row, col=4;
        for(int i=0; i<5; ++i)
        {
            cin.getline(s[i], 6);
            if(s[i][0] == 'Z')
            {
                return 0;
            }
            for(int j=0; j<5; ++j)
            {
                if(s[i][j] == ' ')
                {
                    row = i;
                    col = j;
                }
            }
        }
        bool flag = true;
        char c;
        cin >> c;
        while(c != '0')
        {
            if(flag)
            {
                switch(c)
                {
                    case 'A':
                        if(row > 0)
                        {
                            s[row][col] = s[row-1][col];
                            s[--row][col] = ' ';
                        }
                        else
                        {
                            flag = false;
                        }
                        break;
                    case 'B':
                        if(row < 4)
                        {
                            s[row][col] = s[row+1][col];
                            s[++row][col] = ' ';
                        }
                        else
                        {
                            flag = false;
                        }
                        break;
                    case 'L':
                        if(col > 0)
                        {
                            s[row][col] = s[row][col-1];
                            s[row][--col] = ' ';
                        }
                        else
                        {
                            flag = false;
                        }
                        break;
                    case 'R':
                        if(col < 4)
                        {
                            s[row][col] = s[row][col+1];
                            s[row][++col] = ' ';
                        }
                        else
                        {
                            flag = false;
                        }
                }
            }
            cin >> c;
        }
        if(count)
        {
            cout << endl;
        }
        cout << "Puzzle #" << ++count << ":" << endl;
        if(flag)
        {
            for(int i=0; i<5; ++i)
            {
                for(int j=0; j<4; ++j)
                {
                    cout << s[i][j] << ' ';
                }
                cout << s[i][4] << endl;
            }
        }
        else 
        {
            cout << "This puzzle has no final configuration." << endl;
        }
		cin.get();
    }

    return 0;
}