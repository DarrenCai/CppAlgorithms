/**
 * 竖式问题
 */

#include <iostream>
#include <cstring>
#include <iomanip>

int main()
{
	using namespace std;
	cout << setiosflags(ios::right);
	char s[11] = { 0 };
	cin >> s;

	int count = 0;
	for(int i=100; i<1000; ++i)
	{
		if(strchr(s, '0' + i / 100) && strchr(s, '0' + i / 10 % 10) && strchr(s, '0' + i % 10))
		{
			for(int j=10; j<100; ++j)
			{
				if(strchr(s, '0' + j / 10) && strchr(s, '0' + j % 10))
				{
					bool flag = true;
					int low, high, t;
					low = t = j % 10 * i;
					do
					{
						if(!strchr(s, '0' + t % 10))
						{
							flag = false;
							break;
						}
						t /= 10;
					}while(t);
					if(flag)
					{
						high = t = j / 10 * i;
						do
						{
							if(!strchr(s, '0' + t % 10))
							{
								flag = false;
								break;
							}
							t /= 10;
						}while(t);
					}
					if(flag)
					{
						t = low + 10*high;
						do
						{
							if(!strchr(s, '0' + t % 10))
							{
								flag = false;
								break;
							}
							t /= 10;
						}while(t);
						if(flag)
						{
							cout << setw(0) << "<" << ++count << ">\n  " << i << "\nX  " << j << "\n-----\n" << setw(5)
							<< low << endl << setw(4) << high << " \n-----\n" << setw(5) << low + 10*high << endl << endl;
						}
					}
				}
			}
		}
	}
	cout << "The number of solutions = " << count << endl;
	
	return 0;
}