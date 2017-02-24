/**
 * UVa509
 * RAID技术
 */

#include <iostream>
#include <string>

int main()
{
    using namespace std;
    int count = 0;
    short d, s, b;
    while(cin>>d>>s>>b && d)
    {
        char parity;
        cin >> parity;
		parity == 'O' ? parity = 1 : parity = 0;
        const short D = d;
        string ss[D];
        for(short i=0; i<D; ++i)
        {
            cin >> ss[i];
        }
        bool flag = true;
        for(short j=0; flag && j<b; ++j)
        {
            for(short k=0; flag && k<s; ++k)
            {
                short errors=0, start=-1, bit=0;
                for(short i=0; errors<2 && i<D; ++i)
                {
                    if(ss[i][s*j+k]=='x')
                    {
                        ++errors;
                        start = i;
						continue;
                    }
					bit ^= ss[i][s*j+k] - '0';
                }
                if(errors>1 || (errors==0 && bit!=parity))
                {
                    flag = false;
                    cout << "Disk set " << ++count <<" is invalid." << endl;
                }
                if(errors == 1)
                {
                    ss[start][s*j+k] = parity;
                    for(short i=0; i<D; ++i)
                    {
                        if(i != start)
                        {
                            ss[start][s*j+k] ^= ss[i][s*j+k]-'0';
                        }
                    }
					ss[start][s*j+k] += '0';
                }
            }
        }
        if(flag)
        {
            string ans = "";
            char bit=0, t=0;
            for(short j=0; j<b; ++j)
            {
                for(short i=0; i<D; ++i)
                {
                    if(j%D != i)
                    {
                        for(short k=0; k<s; ++k)
                        {
                            t = (t<<1) + ss[i][s*j+k]-'0';
                            if(++bit == 4)
                            {
                                ans += t<10 ? '0'+t:'A'+t-10;
                                bit=0;
                                t=0;
                            }
                        }
                    }
                }
            }
            if(bit != 0)
            {
                t <<= 4-bit;
                ans += t<10 ? '0'+t:'A'+t-10;
            }
            cout << "Disk set " << ++count <<" is valid, contents are: " << ans << endl;
        }
    }
    return 0;
}