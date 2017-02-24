/**
 * UVa201
 * 正方形
 */

#include <iostream>

struct edge
{
    unsigned char h:4;
    unsigned char v:4;
};

int main()
{
    using namespace std;
    short n, count=0;
    while(cin >> n)
    {
        if(count)
        {
            cout << "\n**********************************\n" << endl;
        }
        cout << "Problem #" << ++count << endl << endl;
        edge s[9][9] = {0};
        short m;
        cin >> m;
        while(m--)
        {
            char c;
            short i, j;
            cin >> c >> i >> j;
            if(c == 'H')
            {
                s[i-1][j-1].h = j;
            }
            else
            {
                s[j-1][i-1].v = j;
            }
        }
        for(short i=n-1; i>=0; --i)
        {
            for(short j=n-1; j>=0; --j)
            {
                if(j-1>=0 && s[i][j].h && s[i][j-1].h)
                {
                    s[i][j-1].h = s[i][j].h;
                }
                if(i-1>=0 && s[i][j].v && s[i-1][j].v)
                {
                    s[i-1][j].v = s[i][j].v;
                }
            }
        }
        short t[8] = { 0 };
        for(short i1=0; i1<n-1; ++i1)
        {
            for(short i2=i1+1; i2<n; ++i2)
            {
                const short size = i2-i1;
                for(short j=0; j+size<n; ++j)
                {
                    if(s[i1][j].h>=j+size && s[i2][j].h>=j+size && s[i1][j].v>=i2 && s[i1][j+size].v>=i2)
                    {
                        ++ t[size-1];
                    }
                }
            }
        }
        bool noSq = true;
        for(short i=0; i<n-1; ++i)
        {
            if(t[i])
            {
                cout << t[i] << " square (s) of size " << i+1 << endl;
                noSq = false;
            }
        }
        if(noSq)
        {
            cout << "No completed squares can be found." << endl;
        }
    }
    return 0;
}