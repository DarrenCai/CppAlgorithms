/**
 * UVa11809
 * 浮点数
 */

#include <iostream>
#include <sstream>
#include <cmath>

int main()
{
    using namespace std;
    int b[10][30];
    double a[10][30];
    for(int i=0; i<10; ++i)
    {
        for(int j=0; j<30; ++j)
        {
            double t = log10(1-pow(2, -i-1)) + (pow(2, j+1) - 1)*log10(2);
            b[i][j] = t;
            a[i][j] = pow(10, t-b[i][j]);
        }
    }
    string s;
    while(cin>>s && s!="0e0")
    {
        s[17] = ' ';
        stringstream ss(s);
        int B;
        double A;
        ss >> A >> B;
        while(A < 1)
        {
            A *= 10;
            -- B;
        }
        for(int i=0; i<10; ++i)
        {
            for(int j=0; j<30; ++j)
            {
                if(b[i][j]==B && fabs(a[i][j] - A) < 4e-4)
                {
                    cout << i << ' ' << j+1 << endl;
                    break;
                }
            }
        }
    }

    return 0;
}