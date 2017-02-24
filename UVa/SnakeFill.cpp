/**
 * 蛇形填数，矩阵的每个元素限制在4位数以内
 */

#include <iostream>
#include <cstring>
#include <iomanip>

enum {L, R, U, D};

int main()
{
	using namespace std;
	
	int i, j;
	cin >> i >> j;
	const int m = i;
	const int n = j;
	int s[m][n], val = 0, direction = D;
	i = 0, j = n-1;
	memset(s, 0, sizeof(s));
	while(++val <= m*n)
	{
		s[i][j] = val;
		if(direction == D)
		{
			if(i < m-1 && !s[i+1][j])
			{
				 ++ i;
			}
			else
			{
				-- j;
				direction = L;
			}
		}
		else if(direction == L)
		{
			if(j > 0 && !s[i][j-1])
			{
				 -- j;
			}
			else
			{
				-- i;
				direction = U;
			}
		}
		else if(direction == U)
		{
			if(i > 0 && !s[i-1][j])
			{
				 -- i;
			}
			else
			{
				++ j;
				direction = R;
			}
		}
		else
		{
			if(j < n-1 && !s[i][j+1])
			{
				 ++ j;
			}
			else
			{
				++ i;
				direction = D;
			}
		}
	}
	cout << setiosflags(ios::left);
	for(i=0; i<m; ++i)
	{
		for(j=0; j<n-1; ++j)
		{
			cout << setw(5) << s[i][j];
		}
		cout << setw(1) << s[i][n-1] << endl;
	}
	
	return 0;
}