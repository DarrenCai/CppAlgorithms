/**
 * UVa232
 * 纵横字谜的答案
 */

#include <iostream>

int main()
{
    using namespace std;
    int r, c, count = 0;
    cin >> r;
    while(r)
    {
		cin >> c;
		cin.get();
        if(count)
        {
            cout << endl;
        }
        cout << "puzzle #" << ++count << ":\nAcross" << endl;
        const int R = r;
        const int C = c;
        char s[R][C+1], num[R][C], t=0;
        for(int i=0; i<r; ++i)
        {
            cin.getline(s[i], c+1);
            for(int j=0, k=0; k<c; ++k)
            {
				if(s[i][k] == '*')
				{
					j = k + 1;
				}
				else
				{
					if(i==0 || k==0 || s[i-1][k]=='*' || s[i][k-1]=='*')
					{
						num[i][k] = ++t;
					}
					if(k==c-1 || s[i][k+1]=='*')
					{
						if(num[i][j] < 10)
						{
							cout << "  " << (int)num[i][j] << '.';
						}
						else
						{
							cout << " " << (int)num[i][j] << '.';
						}
						for(int p=j; p<=k; ++p)
						{
							cout << s[i][p];
						}
						cout << endl;
						j = k + 2;
					}
				}
            }
        }
        cout << "Down" << endl;
		for(int i=0; i<r; ++i)
        {
            for(int j=0; j<c; ++j)
            {
                if(s[i][j] != '*' && (i==0 || s[i-1][j]=='*'))
                {
                    if(num[i][j] < 10)
                    {
                        cout << "  " << (int)num[i][j] << '.' << s[i][j];
                    }
                    else
                    {
                        cout << " " << (int)num[i][j] << '.' << s[i][j];
                    }
                    int k = i + 1;
                    while(k<r && s[k][j]!='*')
                    {
                        cout << s[k++][j];
                    }
                    cout << endl;
                }
            }
        }
		cin >> r;
    }
    return 0;
}