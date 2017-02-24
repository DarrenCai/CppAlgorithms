/**
 * UVa1590
 * IP网络
 * 注意这里是通常的已知网络标识和总主机数的求逆问题，为得到子网掩码一定要从最大ip和最小ip的最高位是否相同来依次倒着判断
 */

#include <iostream>
#include <string>

int main()
{
    using namespace std;
    const unsigned char table[8] = {254, 252, 248, 240, 224, 192, 128, 0};
    int m;
    while(cin >> m)
    {
        unsigned char min[4]={255, 255, 255, 255}, max[4]={0}, mask[4] = {0};
        while(m--)
        {
            char c;
            unsigned short ip[4];
            cin >> ip[0] >> c >> ip[1] >> c >> ip[2] >> c >> ip[3];
            for(c=0; c<4; ++c)
            {
                if(ip[c] < min[c])
                {
                    min[c] = ip[c];
                }
                if(ip[c] > max[c])
                {
                    max[c] = ip[c];
                }
            }
        }
        for(char i=0; i<4; ++i)
        {
            if(min[i] == max[i])
            {
                mask[i] = 255;
            }
            else
            {
                char j;
                for(j=7; j>0 && (min[i]&table[j-1]-table[j]) == (max[i]&table[j-1]-table[j]); --j);
                mask[i] = table[j];
                break;
            }
        }
        cout << short(min[0]&mask[0]) << '.' << short(min[1]&mask[1]) << '.' << short(min[2]&mask[2]) << '.' << short(min[3]&mask[3]) << endl;
        cout << (short)mask[0] << '.' << (short)mask[1] << '.' << (short)mask[2] << '.' << (short)mask[3] << endl;
    }
    return 0;
}